#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "glm/glm.hpp"

class Projectile {
public:
	glm::vec3 pos;
	glm::vec3 vel;
	float speed = 10.0f;
	
	Projectile(glm::vec3 start, glm::vec3 direction) {
		pos = start;
		vel = glm::normalize(direction) * speed;
	}

	inline void update(float dt) {
		pos += vel * dt;
	}

	//inline void draw(const glm::mat4& view, const glm::mat4& proj) {
	//}

	
};

#endif