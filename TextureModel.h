
#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H


#include "modelTexture.h"
#include "rawModel.h"

/*
    Texture Model: Represet Model Data and Texture Data.

            - Raw Model Class: Represet only Model Data not Texture Data

*/

class TexturedModel {

public:
    RawModel rawModel = RawModel();      // RawModel - podaci kao Vertices
    ModelTexture texture = ModelTexture();   // Texture  - predstavlja Texturu koju ima ovaj Model

    TexturedModel();
    TexturedModel(RawModel rawModel, ModelTexture texture);

    bool operator < (const TexturedModel &other) const;

};






#endif
