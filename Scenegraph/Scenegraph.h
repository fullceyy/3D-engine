	#pragma once
#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "../Object/Object.h"
#include "../Player/PlayableCharacter.h"
#include <unordered_map>

class Scenegraph {
	public:
		
		Scenegraph() {}
		~Scenegraph() = default;
	
		void attachObject(std::shared_ptr<Object>);
		//void render();
		void render(const glm::mat4& view, const glm::mat4& projection);
	private:
		std::vector<std::shared_ptr<Object>> sceneObjects;
};

#endif

