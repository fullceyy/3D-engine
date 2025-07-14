#include "Model.h"

Model::Model(std::shared_ptr<Shader> shader) {
	this->mShader = shader;
	mTextures.reserve(3);
}

Model::Model() { mTextures.reserve(3); }


void Model::setObjectShader(std::shared_ptr<Shader> shader) {
	this->mShader = shader;
	if(!mShader) {
		std::cout << "MODEL::SETOBJECTSHADER:: mShader variable is not set!\n";
	}
}

