#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Shader {
	public:
		Shader(const char*, const char*);
		~Shader() {};
		unsigned int CACShaders(unsigned int);
		void bind() const;
		void unbind() const;
		unsigned int program_id;
		/*UNIFORMS*/
		void SUvec3(const std::string& name, glm::vec3 value) const;
		void SUfloat(const std::string& name, float value) const;
		void SUint(const std::string& name, int value) const;
		void SUmat4(const std::string& name, glm::mat4 value) const;

		inline void setType(std::string setType) { type = setType; }
		std::string getType() { return type; }
		GLuint getID() const { return program_id; }
	private:
		std::string vertexShader;
		std::string fragmentShader;
		std::string type;
};

#endif