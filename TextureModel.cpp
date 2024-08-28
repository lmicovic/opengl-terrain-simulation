
#include "rawModel.h"
#include "TextureModel.h"

#include <iostream>

/*
    Texture Model: Represet Model Data and Texture Data.

            - Raw Model Class: Represet only Model Data not Texture Data

*/
TexturedModel::TexturedModel() {

}

TexturedModel::TexturedModel(RawModel rawModel, ModelTexture texture) {

    this->rawModel = rawModel;     // RawModel - podaci kao Vertices
    this->texture = texture;       // Texture  - predstavlja Texturu koju ima ovaj Model

}

    bool TexturedModel::operator < (const TexturedModel &other) const {

        return this->texture.textureID < other.texture.textureID;

    }


