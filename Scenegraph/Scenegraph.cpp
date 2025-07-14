#include "Scenegraph.h"
#include "../Player/bbvsis.hpp"

void Scenegraph::attachObject(std::shared_ptr<Object> obj) {
	if(obj)
	sceneObjects.emplace_back(obj);
	else {
		std::cout << "INVALID SCENEOBJECT::" << obj.get() << "\n";
	}
}

//void Scenegraph::render() {
//	for(auto& object : sceneObjects) {
//		object->draw();
//	}
//
//	std::shared_ptr<Object> player = nullptr;
//	for(auto& object : sceneObjects) {
//		if(object->getObjTag() == Tag::Player) {
//			player = object;
//			break;
//		}
//	}
//
//	for(auto& object : sceneObjects) {
//		if (object == player) continue; // Skip self-collision
//		if(Bounding_Box::checkColl(player->getWorldAABB(), object->getWorldAABB())) {
//			std::cout << "collision detected with : " << object->getObjTag() << "\n";
//		}		
//	}
//}

void Scenegraph::render(const glm::mat4& view, const glm::mat4& projection) {

	sceneObjects.erase(
		std::remove_if(sceneObjects.begin(), sceneObjects.end(),
			[](const std::shared_ptr<Object>& obj) {
				return obj->getObjTag() == Tag::Destroyed;
			}),
		sceneObjects.end());
	
	// First render all objects normally
	for (auto& object : sceneObjects) {
		object->draw(view, projection);
	}

	// Find player object
	std::shared_ptr<Object> player = nullptr;
	for (auto& object : sceneObjects) {
		if (object->getObjTag() == Tag::Player) {
			player = object;
			break;
		}
	}

	PlayableCharacter* randomPointer = dynamic_cast<PlayableCharacter*>(player.get());
	randomPointer->storeObjects(sceneObjects);

	for (auto& object : sceneObjects) {
		if (object == player) continue; // Skip self-collision

		Tag tag = object->getObjTag();
		if (tag == Tag::NonCollidable || tag == Tag::Nonset || tag == Tag::Breakable) continue;

		auto pbb = player->getWorldAABB();
		auto obb = object->getWorldAABB();

		if (Bounding_Box::checkColl(pbb, obb)) {
			std::cout << "COLLISION DETECTED:\n";
			std::cout << "obb pos: " << object->globalPosition;
			if(randomPointer) {
				randomPointer->resolveCollision(object);
			}
		}
	}
}


/*ACTUAL REDNERER */
//void Scenegraph::render(const glm::mat4& view, const glm::mat4& projection) {
//	for(auto& object : sceneObjects) {
//		object->draw(view, projection);
//	}
//
//	std::shared_ptr<Object> player = nullptr;
//	for(auto& object : sceneObjects) {
//		if(object->getObjTag() == Tag::Player) {
//			player = object;
//			// remove the player from being a part of the scene?
//			// or just skip if found
//			//sceneObjects.erase(std::find(sceneObjects.begin(), sceneObjects.end(), object));
//			break;
//		}
//		//BoundingBoxVisualizer bbv(object->getObjBB(), object);
//		//bbv.draw(GL_TRIANGLES);
//	}
//
//	//for(auto& object : sceneObjects) {
//	//	if (object == player) continue; // Skip self-collision
//	//	Tag tag = object->getObjTag();
//	//	if (tag == Tag::NonCollidable || tag == Tag::Nonset) continue;
//	//	if(Bounding_Box::checkColl(player->getWorldAABB(), object->getWorldAABB())) {
//	//		// cast objtag?
//	//		std::cout << "collision detected with : " << object->getObjTag() << "\n";
//	//	}		
//	//}
//
//	for (auto& object : sceneObjects) {
//		if (object == player) continue; // Skip self-collision
//
//		Tag tag = object->getObjTag();
//		if (tag == Tag::NonCollidable || tag == Tag::Nonset) continue;
//
//		auto pbb = player->getWorldAABB();
//		auto obb = object->getWorldAABB();
//
//		if (Bounding_Box::checkColl(pbb, obb)) {
//			std::cout << "COLLISION DETECTED:\n";
//			std::cout << "Player position: " << glm::to_string(player->globalPosition) << "\n";
//			std::cout << "Player AABB: min " << glm::to_string(pbb.minObjectVal)
//				<< ", max " << glm::to_string(pbb.maxObjectVal) << "\n";
//			std::cout << "Object position: " << glm::to_string(object->globalPosition) << "\n";
//			std::cout << "Object AABB: min " << glm::to_string(obb.minObjectVal)
//				<< ", max " << glm::to_string(obb.maxObjectVal) << "\n";
//			std::cout << "Object transform:\n" << glm::to_string(object->transform()) << "\n";
//		}
//	}
//
//}

//void Scenegraph::addSceneChild(Node* sceneChild) {
//	/*
//	I think in main I will just create a vector of nodes and then do
//	for loop which will iterate through each and will call addSceneChild for each scene node ->
//	created in the main.cpp.
//	*/
//
//	if (sceneChild) {
//		this->sceneObjects.push_back(sceneChild);
//	} else {
//		std::cout << "SCENEGRAPH::ADDSCENECHILD::sceneChild Node* invalid!\n";
//	}
//}
//
//void Scenegraph::renderScene() {
//	for (const auto objects : sceneObjects) {
//		objects->drawNodeTesting();
//	}
//}

	// Store visualizers persistently (as member variable)
	//static std::unordered_map<std::shared_ptr<Object>, std::unique_ptr<BoundingBoxVisualizer>> visualizers;
	//std::vector<std::shared_ptr<Object>> collidableObjects;
	//static std::vector<std::unique_ptr<BoundingBoxVisualizer>> vs;
	// Render wireframes for all collidable objects
	//for (auto& object : sceneObjects) {
	//	int q = 0;
	//	Tag tag = object->getObjTag();
	//	if (tag == Tag::Collidable) {
	//		//collidableObjects.emplace_back(object);
	//		vs[q] = std::make_unique<BoundingBoxVisualizer>(object);
	//		vs[q]->draw();
	//		/*if (visualizers.find(object) == visualizers.end()) {
	//			visualizers[object] = std::make_unique<BoundingBoxVisualizer>(object);
	//		}*/
	//		// Update and draw wireframe
	//		//visualizers[object]->draw();
	//		q++;
	//	}
	//}