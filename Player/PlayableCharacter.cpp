#include "PlayableCharacter.h"

void PlayableCharacter::setup() {
	POV = std::make_unique<Camera>(glm::vec3(0.f),
			glm::vec3(0.0f, 1.0f, 0.0f), YAW, PITCH);

	this->setObjBB(glm::vec3(-0.2f), glm::vec3(0.2f));
}
// use std::unordered_map for shader strong instead of each object storing its own shader.


void PlayableCharacter::fireWeapon() {
	std::cout << "Weapon was fired!\n";
	if (!POV) return;

	glm::vec3 rayOrigin = POV->Pos;
	glm::vec3 rayDir = glm::normalize(POV->Front);
	std::cout << "Ray Direction: " << glm::to_string(rayDir) << "\n";

	float closestHitDistance = FLT_MAX;
	std::shared_ptr<Object> closestObject = nullptr;

	for (const auto& sceneObject : objectStorage) {
		Tag tag = sceneObject->getObjTag();
		if (tag != Tag::Breakable && tag != Tag::Collidable)
			continue;

		Bounding_Box aabb = sceneObject->getWorldAABB();
		float hitDistance;
		if (Bounding_Box::rayIntersectsAABB(rayOrigin, rayDir, aabb, hitDistance)) {
			if (hitDistance < closestHitDistance) {
				closestHitDistance = hitDistance;
				closestObject = sceneObject;
			}
		}
	}
	if (this->am == true && closestObject) {
		Selector::DetectSelection(closestObject);
	}
	if (closestObject && this->am == false) {
		Tag tag = closestObject->getObjTag();
		if (tag == Tag::Breakable) {
			closestObject->setObjTag(Tag::Destroyed);
			std::cout << "Hit breakable object at: " << glm::to_string(closestObject->globalPosition) << "\n";
			// TODO: Remove or mark the object as destroyed
		} else if (tag == Tag::Collidable) {
			std::cout << "Shot blocked by solid object at: " << glm::to_string(closestObject->globalPosition) << "\n";
		}
	} else {
		std::cout << "No object hit.\n";
	}
}


void PlayableCharacter::update(float dt) {
	this->lastSafePos = globalPosition;
	this->globalPosition = temporalPlayerPosition;
	POV->Pos = globalPosition + glm::vec3(0.f, -0.3f, 0.f); // if not for this offset the camera Y axis is not preserved!
	POV->updateCameraVectors();
}

void PlayableCharacter::processPlayerInput(float deltaTime) {
	glm::vec3 forward = glm::normalize(glm::vec3(POV->Front.x, 0.0f, POV->Front.z));
	glm::vec3 right = glm::normalize(glm::cross(forward, POV->Up));

	if (glfwGetKey(POV->cameraGetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		this->temporalPlayerPosition += forward * 0.2f * deltaTime;
	}
	if (glfwGetKey(POV->cameraGetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		this->temporalPlayerPosition -= forward * 0.2f * deltaTime;
	}
	if (glfwGetKey(POV->cameraGetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		this->temporalPlayerPosition -= right * 0.2f * deltaTime;
	}
	if (glfwGetKey(POV->cameraGetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		this->temporalPlayerPosition += right * 0.2f * deltaTime;
	}
	/*0.2f constant speed of a player.*/
}

void PlayableCharacter::processPlayerInput(float deltaTime, InputSystem* input) {
	glm::vec3 forward = glm::normalize(glm::vec3(POV->Front.x, 0.0f, POV->Front.z));
	glm::vec3 right = glm::normalize(glm::cross(forward, POV->Up));
	const float walkSpeed = 0.5f;
	const float runSpeed = 2.0f;

	float speed = walkSpeed;
	if (input->isKeyHeld(GLFW_KEY_LEFT_SHIFT)) {
		speed = runSpeed;
	}
	speed *= deltaTime;

	if (input->isKeyHeld(GLFW_KEY_W)) {
		temporalPlayerPosition += forward * speed;
	}
	if (input->isKeyHeld(GLFW_KEY_S)) {
		temporalPlayerPosition -= forward * speed;
	}
	if (input->isKeyHeld(GLFW_KEY_A)) {
		temporalPlayerPosition -= right * speed;
	}
	if (input->isKeyHeld(GLFW_KEY_D)) {
		temporalPlayerPosition += right * speed;
	}

	if (input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		std::cout << "LEFT MB PRESSED:\n";
		this->fireWeapon();
	}

		float dx = input->getMouseDeltaX();
		float dy = input->getMouseDeltaY();

		POV->yaw += dx * POV->sens;
		POV->pitch += dy * POV->sens;

		POV->pitch = glm::clamp(POV->pitch, -89.0f, 89.0f);

		glm::vec3 direction;
		direction.x = cos(glm::radians(POV->yaw)) * cos(glm::radians(POV->pitch));
		direction.y = sin(glm::radians(POV->pitch));
		direction.z = sin(glm::radians(POV->yaw)) * cos(glm::radians(POV->pitch));

		POV->Front = glm::normalize(direction);
		POV->updateCameraVectors();
}

void PlayableCharacter::resolveCollision(std::shared_ptr<Object> object) {
	glm::vec3 tryMove = temporalPlayerPosition - lastSafePos;
	glm::vec3 resolvedPos = lastSafePos;

	this->globalPosition = lastSafePos + glm::vec3(tryMove.x, 0, 0);
	if (!Bounding_Box::checkColl(this->getWorldAABB(), object->getWorldAABB())) {
		resolvedPos.x += tryMove.x;
	}

	this->globalPosition = lastSafePos + glm::vec3(0, 0, tryMove.z);
	if (!Bounding_Box::checkColl(this->getWorldAABB(), object->getWorldAABB())) {
		resolvedPos.z += tryMove.z;
	}

	// Apply corrected position
	globalPosition = resolvedPos;
	temporalPlayerPosition = resolvedPos;
	POV->Pos = resolvedPos;
}
