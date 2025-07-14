#include "Plane.h"

void Plane::setup() {
	std::vector<Vertex> planeVertices = {
	{{-50.0f, 0.0f, -50.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
	{{ 50.0f, 0.0f, -50.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
	{{ 50.0f, 0.0f,  50.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
	{{-50.0f, 0.0f,  50.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}
	};
	this->vertices = planeVertices;

	std::vector<uint32_t> planeIndices = {
		0, 1, 2,
		2, 3, 0
	};
	this->indices = planeIndices;

	mesh = std::make_shared<Mesh>(planeVertices, planeIndices);

	if(getObjTag() == Tag::Collidable) {
		auto xyz = mesh->getVerts();
		min = xyz[0];
		max = xyz[0];
		for (int q = 0; q < xyz.size(); q++) {
			min = glm::min(xyz[q], min);
			max = glm::max(xyz[q], max);
		}
	std::cout << "SPLANE::SETUP::MIN value : " << min << "\n";
	std::cout << "SPLANE::SETUP::MAX value : " << max << "\n";
		this->setObjBB(min, max);
	
	}
}