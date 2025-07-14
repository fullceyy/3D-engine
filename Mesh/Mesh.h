#pragma once
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "Vertex.h"
#include "STexture.h"
#include "wfVertex.h"
//#include "collision/Collision.h"

class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
		//Mesh(std::vector<wfVertex> vertices, std::vector<uint32_t> indices, bool wf);
		virtual ~Mesh() {};

		void draw();
		void draw(GLenum);

		inline std::vector<glm::vec3> getVerts() const { return eachVertexXYZ; }
		inline std::vector<glm::vec3> getNorms() const { return eachVertexNormals; }
		inline std::vector<uint32_t> getInds() const { return indices; }
		inline std::vector<glm::vec2> getTexs() const { return texas; }
	private:
		void setupMesh();
		//void setupMesh(bool wf);

		unsigned int vao;
		unsigned int vbo;
		unsigned int ebo;

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<STexture> textures;

		std::vector<glm::vec3> eachVertexXYZ;
		std::vector<glm::vec3> eachVertexNormals;
		std::vector<glm::vec2> texas; // ?

		//std::vector<wfVertex> wfVertices;
		//std::vector<uint32_t> wfIndices;
};

#endif
