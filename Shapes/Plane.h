#pragma once
#ifndef PLANE_H
#define PLANE_H

#include "../Object/Object.h"

class Plane : public Object {
public:
	Plane(float size, Tag tag) : Object() {
		this->scaleSize = size;
		this->setObjTag(tag);
		setup();
	}
	~Plane() {}

private:
	float scaleSize;
	void setup();
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec3 min{ -FLT_MAX };
	glm::vec3 max{ FLT_MAX };
};

#endif
