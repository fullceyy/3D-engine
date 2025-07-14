#pragma once
#ifndef NODE_H
#define NODE_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include"GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <glm/gtx/euler_angles.hpp>


#include <iostream>
#include <vector>
#include <algorithm>

class Node {
	public:
		bool visible = false;
		/*CONSTRUCTOR + DECONSTRUCTOR*/
		Node() = default;
		
		virtual ~Node();
		/*PARENT RELATED METHODS*/
		Node* parent() const;
		void reparent(Node*);
		/*CHILD RELATED METHODS*/
		void addChild(Node*);
		void removeChild(Node*);
		/*MODEL*/
		glm::mat4 transform() const;
		glm::mat4 view() const;
		/*GLOBAL SPACE DECLARATIONS*/
		glm::vec3 globalPosition	{ 0.0f };
		glm::vec3 globalRotation	{ 0.0f };
		glm::vec3 globalScale		{ 1.0f };
		/*RETURN PARENT + CHILD GLOBALPOS/ROT*/
		glm::vec3 globalPos() const;
		glm::vec3 globalRot() const;
		/*DRAW CALL*/
		//virtual void draw() = 0;
	private:
		Node* parentNode = nullptr;
		std::vector<Node*> childrenNodes {};
};

#endif