#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::~Texture() {
    glDeleteTextures(1, &texture_id);
}

Texture::Texture(const char* fn, std::string type) {
    stbi_set_flip_vertically_on_load(true);

    LoadedData = stbi_load(fn, &width, &height, &numberOfColorChannels, 3);

    if (LoadedData) {
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, LoadedData);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(LoadedData);
    } else {
        std::cout << "Failed to load provided texture! : " << fn << " " <<
            stbi_failure_reason() << std::endl;
    }
    this->type = type;
    std::cout << type << "\n";
}

void Texture::bindTX(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbindTX(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getTXID() const {
    return texture_id;
}