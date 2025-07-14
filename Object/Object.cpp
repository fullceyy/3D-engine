#include "Object.h"

void Object::setTexture(std::shared_ptr<Texture> tex) {
	mTextures.emplace_back(tex);
}

void Object::setObjBB(glm::vec3 min, glm::vec3 max) {
	this->objectBbox.maxObjectVal = max;
	this->objectBbox.minObjectVal = min;
}

void Object::setObjTag(Tag OT) {
	this->objectTag = OT;
} 


Bounding_Box Object::getWorldAABB() const {
	Bounding_Box result;

	glm::mat4 model = this->transform();
	glm::vec3 min = this->objectBbox.minObjectVal;
	glm::vec3 max = this->objectBbox.maxObjectVal;

	// Generate all 8 corners of the AABB in local space
	std::vector<glm::vec3> corners = {
		{min.x, min.y, min.z},
		{min.x, min.y, max.z},
		{min.x, max.y, min.z},
		{min.x, max.y, max.z},
		{max.x, min.y, min.z},
		{max.x, min.y, max.z},
		{max.x, max.y, min.z},
		{max.x, max.y, max.z}
	};

	glm::vec3 newMin(FLT_MAX);
	glm::vec3 newMax(-FLT_MAX);

	for (const auto& corner : corners) {
		glm::vec3 transformed = glm::vec3(model * glm::vec4(corner, 1.0f));
		newMin = glm::min(newMin, transformed);
		newMax = glm::max(newMax, transformed);
	}

	result.minObjectVal = newMin;
	result.maxObjectVal = newMax;

	return result;
}

//void Object::draw() {
//	auto& temp_s = getShader();
//	//std::cout << "TEMP_S" << temp_s->getType() << "\n";
//	Mesh* temp_m = getMesh();
//	//std::cout << "TEMP_M" << temp_m << "\n";
//	auto& temp_tvec = getTexturesRef();
//	//std::cout << "TEMP_TVEC" << &temp_tvec << "\n";
//	if (temp_s && temp_m) {
//		temp_s->bind();
//		temp_s->SUmat4("model", this->transform());
//		uint32_t q = 0;
//		if(!temp_tvec.empty()) {
//			unsigned int diffuseNr = 1;
//			unsigned int speculaNr = 1;
//			std::string tn;
//			for (auto& tex : temp_tvec) {
//				if (tex->getType() == "texture_specular")
//					tn = std::to_string(speculaNr++);
//				else if (tex->getType() == "texture_diffuse")
//					tn = std::to_string(diffuseNr++);
//
//				std::string path = "material." + tex->getType() + tn;
//				//std::cout << path << "\n";
//				temp_s->SUint(path, q);
//				glActiveTexture(GL_TEXTURE0 + q);  // Must set active texture unit first!
//				glBindTexture(GL_TEXTURE_2D, tex->getTXID());
//				q++;
//			}
//		}
//		temp_m->draw();
//	}
//}

void Object::draw(const glm::mat4& view, const glm::mat4& projection) {
	auto& temp_s = getShader();
	auto& temp_m = getMeshRef();
	auto& temp_tvec = getTexturesRef();
	if (temp_s) { // if (temp_s && temp_m) {
 		temp_s->bind();
		temp_s->SUmat4("view", view);
		temp_s->SUmat4("projection", projection);
		glm::mat4 model = this->transform();
		temp_s->SUmat4("model", model);
		uint32_t q = 0;
		if(!temp_tvec.empty()) {
			unsigned int diffuseNr = 1;
			unsigned int speculaNr = 1;
			std::string tn;
			for (auto& tex : temp_tvec) {
				if (tex->getType() == "texture_specular")
					tn = std::to_string(speculaNr++);
				else if (tex->getType() == "texture_diffuse")
					tn = std::to_string(diffuseNr++);

				std::string path = "material." + tex->getType() + tn;
				//std::cout << path << "\n";
				temp_s->SUint(path, q);
				glActiveTexture(GL_TEXTURE0 + q);  // Must set active texture unit first!
				glBindTexture(GL_TEXTURE_2D, tex->getTXID());
				q++;
			}
		}
		//std::cout << this << " GLOBALPOS : " << this->globalPosition << "\n";
		temp_m->draw();
	}
}


//void Model::draw() {
//	if (mShader && mesh) {
//		Node::draw();
//		// modelMatrix
//		glm::mat4 mm = this->transform();
//		mShader->bind();
//		mShader->SUmat4("model", mm);
//
//		if (!mTextures.empty()) {
//			unsigned int diffuseNr = 1;
//			unsigned int specularNr = 1;
//			std::string textureNumber;
//			/*texture->bindTX(0);*/
//			for (int q = 0; q < mTextures.size(); q++) {
//				//std::cout << "MODEL::TEXTURE::Working with : " << mTextures[q]->getType() << "\n";
//				glActiveTexture(GL_TEXTURE0 + q);
//
//
//				if (mTextures[q]->getType() == "texture_diffuse")
//				{
//					textureNumber = std::to_string(diffuseNr++);
//				} else if (mTextures[q]->getType() == "texture_specular")
//				{
//					textureNumber = std::to_string(specularNr++);
//				}
//				std::string path = "material." + mTextures[q]->getType() + textureNumber;
//				//mShader->SUint("t1", 0);
//				mShader->SUint(path, q);
//				glBindTexture(GL_TEXTURE_2D, mTextures[q]->getTXID());
//			}
//		} else {
//			//std::cout << "MODEL::DRAW::Textures vector is empty! on model: " << this << "\n";
//
//
//			//mShader->SUvec3("light.position", globalPosition);
//		}
//		mesh->draw();
//	}
//}
