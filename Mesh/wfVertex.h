#pragma once
#ifndef WFVERTEX_H
#define WFVERTEX_H

#include "glm/glm.hpp"


struct wfVertex {
	glm::vec3 pos;
	glm::vec3 normals;
	glm::vec2 tex;
	glm::vec3 color;


	wfVertex(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 normals = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec2 text = glm::vec2(0.0f, 0.0f),
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)) {
		this->pos = pos;
		this->normals = normals;
		this->tex = text;
		this->color = color;
	}
};



#endif