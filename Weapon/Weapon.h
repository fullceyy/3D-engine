#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include "glm/glm.hpp"

class Weapon {
public:
	Weapon() {};
	virtual ~Weapon() = default;
	inline void updateWeaponPos(glm::vec3 newPos) { this->weaponPos = newPos; }

	virtual void fireWeapon() = 0;
	
private:
	glm::vec3 weaponPos { 0.0f };
};

#endif