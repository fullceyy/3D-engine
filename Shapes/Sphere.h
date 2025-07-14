#pragma once

#include "../Object/Object.h"
#include <cmath>

class Sphere : public Object {
public:
	Sphere(float radius, Tag tag) : Object() {
		// this->globalPosition = glm::vec3(5.0f);
		this->radius = radius;
		this->setObjTag(tag);
		setup(36, 18);
	}

	Sphere(float radius, Tag tag, glm::vec3 pos) : Object() {
		this->radius = radius;
		this->globalPosition = pos;
		this->setObjTag(tag);
		setup(36, 18);
	}
private:
	float radius;
	void setup(int sectors, int stacks);
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec3 min{-FLT_MAX};
	glm::vec3 max{FLT_MAX};
};