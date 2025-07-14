#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "../Object/Object.h"

class Cube : public Object {
public:
	Cube(float size, Tag tag) : Object() {
		this->scaleSize = size;
		this->setObjTag(tag);
		setup();
	}
	Cube(float size, Tag tag, glm::vec3 pos) : Object() {
		this->scaleSize = size;
		this->globalPosition = pos;
		this->setObjTag(tag);
		setup();
	}
	~Cube() {}
private:
	float scaleSize;
	void setup();
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::vec3 min{-FLT_MAX};
	glm::vec3 max{FLT_MAX}; 
};

#endif

//std::vector<Vertex> cubeVertices = {
//{{-1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
//{{ 1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
//{{ 1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
//{{-1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
//// Back Face
//{{-1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
//{{ 1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
//{{ 1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//{{-1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
//// Left Face
//{{-1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//{{-1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
//{{-1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
//{{-1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
//// Right Face
//{{ 1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//{{ 1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
//{{ 1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
//{{ 1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
//// Bottom Face
//{{-1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
//{{ 1.0f * scaleSize, -1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
//{{ 1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
//{{-1.0f * scaleSize, -1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
//// Top Face
//{{ 1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
//{{-1.0f * scaleSize,  1.0f * scaleSize, -1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
//{{-1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
//{{ 1.0f * scaleSize,  1.0f * scaleSize,  1.0f * scaleSize}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
//};
