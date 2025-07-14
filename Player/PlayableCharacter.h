#pragma once
#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include "../Object/Object.h"
#include "../Camera/Camera.h"
#include "../InputSystem/InputSystem.h"
#include "../Weapon/Weapon.h"
#include "../Selector/Selector.h"

// Forward declaration
class Camera;
class InputSystem;
class Selector;
//class Weapon;

class PlayableCharacter : public Object, public Weapon {
public:
	PlayableCharacter(glm::vec3 pos) : Object() {
		this->temporalPlayerPosition = pos;
		this->globalPosition = pos;
		this->globalScale = glm::vec3(1.0f);
		this->setObjTag(Tag::Player);
		std::cout << "Player scale: " << glm::to_string(globalScale) << "\n";
		setup();
	}
	PlayableCharacter() : Object() {
		this->temporalPlayerPosition = { 0.0f, 0.0f, 0.0f };
		this->globalPosition = temporalPlayerPosition;
		this->setObjTag(Tag::Player);
		setup();
	}

	void fireWeapon() override;
	inline void setAdminMode(bool set) { this->am = set; }
	inline void setParentMode(bool set) { this->pm = set; }

	void processPlayerInput(float);
	void processPlayerInput(float, InputSystem*);
	void update(float);
	void resolveCollision(std::shared_ptr<Object>);
	inline void storeObjects(std::vector<std::shared_ptr<Object>>& objs) { this->objectStorage = objs; }

	inline std::unique_ptr<Camera>& cameraRef() { return POV; }
	/*Example: 
		PlayableCharacter* p = new PlayableCharacter();
		p->cameraRef.get().cameraCurrentWorkingWindow(window);
		*/
	glm::vec3 temporalPlayerPosition;
	glm::vec3 lastSafePos;
private:
	bool am = false;
	bool pm = false;
	void setup();
	std::unique_ptr<Camera> POV;
	std::vector<std::shared_ptr<Object>> objectStorage;
};

#endif