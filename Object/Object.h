#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include "glm/glm.hpp"
#include "../Model/Model.h"
#include "../Model/Node.h"
#include "../Player/Boundingbox.h"

enum Tag {
	Nonset, // no tag is set
	Collidable, // collidable object
	NonCollidable, // non collidable object e.g lighting sources
	Player, // player object
	Breakable,
	Destroyed
};

class Object : public Model, public Node {
public:
	/*CONSTRUCTOR + DECONSTRUCTOR*/
	Object() : Model(), Node() { this->objectTag = Tag::Nonset; }
	virtual ~Object() = default;
	/*DRAW CALL*/
	//void draw() override;
	void draw(const glm::mat4& view, const glm::mat4& projection);
	/*GETTERS*/
	inline Bounding_Box getObjBB() const { return objectBbox; }
	inline Tag getObjTag() const { return objectTag; }
	Bounding_Box getWorldAABB() const;
	/*inline glm::vec3 getObjPos() const { return objPos; }*/
	/*SETTERS*/
	//void setTexture(std::shared_ptr<Texture>) override;
	void setTexture(std::shared_ptr<Texture> tex) override;
	//void setObjPos(glm::vec3);
	void setObjBB(glm::vec3 min, glm::vec3 max);
	void setObjTag(Tag OT);
private:
	//glm::vec3 objPos{0.0f, 0.0f, 0.0f};
	Bounding_Box objectBbox;
	Tag objectTag;
	// shader stored in model.h
};

#endif