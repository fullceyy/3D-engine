#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <iostream>

class Texture {
public:
    Texture(const char* fn, std::string type);
    virtual ~Texture();
    void bindTX(int) const;
    void unbindTX(int) const;
    int getTXID() const;
    inline std::string getType() { return type; }
private:
    int width;
    int height;
    int numberOfColorChannels;

    unsigned char* LoadedData;
    unsigned int texture_id;

    std::string type;
};

#endif