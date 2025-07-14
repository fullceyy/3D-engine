#pragma once

#include "../Scenegraph/Scenegraph.h"
#include "../Shapes/Sphere.h"

#include <random>

class Spawner {
public:
	Spawner() = delete;
	Spawner(const Spawner&) = delete;
	Spawner(Spawner&&) = delete;

	static void SpawnSpheres(int count, 
		Scenegraph* sg, 
		std::shared_ptr<Shader> shader, 
		std::shared_ptr<Texture> d, 
		std::shared_ptr<Texture> s);
};


void Spawner::SpawnSpheres(int count,
	Scenegraph* sg,
	std::shared_ptr<Shader> shader,
	std::shared_ptr<Texture> d,
	std::shared_ptr<Texture> s) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distX(-5.0f, 5.0f);
	std::uniform_real_distribution<float> distZ(-5.0f, 5.0f);
	std::uniform_real_distribution<float> distFloatY(0.5f, 1.5f);

	// 10 collidable cubes at y = 0
	float exclusionRadius = 1.0f;
	for(int q = 0; q < count; q++) {
		auto sphere = std::make_shared<Sphere>(0.15f, Tag::Breakable);
		glm::vec3 randomPos;
		do {
			randomPos = glm::vec3(distX(gen), distFloatY(gen), distZ(gen));
		} while (glm::length(glm::vec3(randomPos.x, 0.0f, randomPos.z)) < exclusionRadius);
		sphere->globalPosition = randomPos;
		sphere->setObjectShader(shader);
		sphere->setTexture(d);
		sphere->setTexture(s);
		sg->attachObject(sphere);
	}
}