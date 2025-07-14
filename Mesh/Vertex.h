#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 normals;
	glm::vec2 tex;

	Vertex(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 normals = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec2 tex = glm::vec2(0.0f, 0.0f)) {
		this->pos = pos;
		this->normals = normals;
		this->tex = tex;
	}
};


#endif