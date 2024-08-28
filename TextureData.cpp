
#include "TextureData.hpp"

TextureData::TextureData() {

}

TextureData::TextureData(unsigned int textureID ,int width, int height, unsigned char* data) {

    this->textureID = textureID;
    this->width = width;
    this->height = height;
    this->data = data;

}
