#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "../Mesh/Mesh.h"
#include "../Shader/Shader.h"
//#include "Node.h"
#include "../Texture/Texture.h"
#include <memory>

class Model {
	public:
		/*CONSTRUCTORS + DESTRUCTOR*/
		Model(std::shared_ptr<Shader> shader);
		Model();
		virtual ~Model() = default;
		/*SETTERS*/
		void setObjectShader(std::shared_ptr<Shader> shader);
		//virtual void setTexture(Texture*);
		/*PASS A REFERENCE INSTEAD OF PATH AND TYPE*/
		//I DON'T KNOW WHY BUT IT REALLY WANTS TO BE A PURE VIRTUAL FUNCTION
		virtual void setTexture(std::shared_ptr<Texture> tex) = 0;
		/*GETTERS*/
		inline Mesh* getMesh() const { return mesh.get(); }
		inline std::shared_ptr<Mesh>& getMeshRef() { return mesh; }
		//inline Shader* getShader() { return mShader; }
		inline std::shared_ptr<Shader>& getShader() { return mShader; }
		// reference return
		inline std::vector<std::shared_ptr<Texture>>& getTexturesRef() { return mTextures; }
		// the getter below might be allocating space for another std::vector in return clause
		// probably memory inefficient, create a copy of it, so using REF method is better
		inline std::vector<std::shared_ptr<Texture>> getTextures() { return mTextures; }

	protected:
		std::shared_ptr<Mesh> mesh;
		std::vector<std::shared_ptr<Texture>> mTextures;
	private:
		//std::vector<std::shared_ptr<Texture>> mTextures;
		std::shared_ptr<Shader> mShader; // should this be uPtr?
};


#endif
