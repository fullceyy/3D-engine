#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices) {
	this->vertices = vertices;
	this->indices = indices;


	std::cout << "Vertices: " << this->vertices.size() << " Indices: " << this->indices.size() << std::endl;

	unsigned int it;
	for (it = 0; it < vertices.size(); it++) {
		glm::vec3 xyz = glm::vec3(vertices[it].pos);
		glm::vec3 normals = glm::vec3(vertices[it].normals);
		glm::vec2 tex = glm::vec2(vertices[it].tex);

		this->eachVertexXYZ.resize(vertices.size());
		this->eachVertexNormals.resize(vertices.size());
		this->texas.resize(vertices.size());

		this->eachVertexXYZ[it].x = xyz.x;
		this->eachVertexXYZ[it].y = xyz.y;
		this->eachVertexXYZ[it].z = xyz.z;
		// print out the values to see if they are set correctly

		this->eachVertexNormals[it].x = normals.x;
		this->eachVertexNormals[it].y = normals.y;
		this->eachVertexNormals[it].z = normals.z;

		this->texas[it].x = tex.x;
		this->texas[it].y = tex.y;
	}
	setupMesh();
}

//Mesh::Mesh(std::vector<wfVertex> vertices, std::vector<uint32_t> indices, bool wf) {
//	this->wfVertices = vertices;
//	this->wfIndices = indices;
//
//
//	std::cout << "Vertices: " << this->vertices.size() << " Indices: " << this->indices.size() << std::endl;
//
//	int it;
//	for (it = 0; it < vertices.size(); it++) {
//		glm::vec3 xyz = glm::vec3(vertices[it].pos);
//		glm::vec3 normals = glm::vec3(vertices[it].normals);
//		glm::vec2 tex = glm::vec2(vertices[it].tex);
//
//		this->eachVertexXYZ.resize(vertices.size());
//		this->eachVertexNormals.resize(vertices.size());
//		this->texas.resize(vertices.size());
//
//		this->eachVertexXYZ[it].x = xyz.x;
//		this->eachVertexXYZ[it].y = xyz.y;
//		this->eachVertexXYZ[it].z = xyz.z;
//
//		this->eachVertexNormals[it].x = normals.x;
//		this->eachVertexNormals[it].y = normals.y;
//		this->eachVertexNormals[it].z = normals.z;
//
//		this->texas[it].x = tex.x;
//		this->texas[it].y = tex.y;
//	}
//	setupMesh(wf);
//}

void Mesh::draw() {
	glBindVertexArray(vao);

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::draw(GLenum type) {
	glBindVertexArray(vao);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	GLint polygonMode[2];
	glGetIntegerv(GL_POLYGON_MODE, polygonMode);

	// Set to wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawElements(type, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode[0]);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void Mesh::setupMesh() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}

//void Mesh::setupMesh(bool wf) {
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(wfVertex), vertices.data(), GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(wfVertex), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(wfVertex), (void*)offsetof(wfVertex, normals));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(wfVertex), (void*)offsetof(wfVertex, tex));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(wfVertex), (void*)offsetof(wfVertex, color));
//	glEnableVertexAttribArray(3);
//
//	glGenBuffers(1, &ebo);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
//
//	glBindVertexArray(0);
//}