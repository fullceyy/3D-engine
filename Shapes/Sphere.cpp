#include "Sphere.h"

void Sphere::setup(int sectors, int stacks) {
	vertices.clear();
	indices.clear();

	const float PI = 3.14159265358979323846f;

	for(int stack = 0; stack <= stacks; ++stack) {
		float stackAngle = PI / 2 - stack * (PI / stacks);
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);

		for(int sector = 0; sector <= sectors; ++sector) {
			float secAngle = sector * (2 * PI / sectors);
			float x = xy * cosf(secAngle);
			float y = xy * sinf(secAngle);
			glm::vec3 normal = glm::normalize(glm::vec3(x, y, z));

			float u = (float)sector / sectors;
			float v = (float)stack / stacks;


			vertices.push_back(Vertex({ x, y, z }, { normal.x, normal.y, normal.z }, { u, v }));
		}
	}	

	for(int stack = 0; stack < stacks; ++stack) {
		int top = stack * (sectors + 1);
		int bot = top + sectors + 1;

		for(int sector = 0; sector < sectors; ++sector) {
			indices.push_back(top + sector);
			indices.push_back(bot + sector);
			indices.push_back(top + sector + 1);

			indices.push_back(top + sector + 1);
			indices.push_back(bot + sector);
			indices.push_back(bot + sector + 1);
		}
	}

	mesh = std::make_shared<Mesh>(vertices, indices);

	auto tag = getObjTag();
	if (tag == Tag::Collidable || tag == Tag::Breakable) {
		auto xyz = mesh->getVerts();
		min = xyz[0];
		max = xyz[0];
		for (int q = 0; q < xyz.size(); q++) {
			min = glm::min(xyz[q], min);
			max = glm::max(xyz[q], max);
		}
		std::cout << "Collision Box for " << this << ": "
			<< min << " to " << max << "\n";
		this->setObjBB(min, max);
	}
}
