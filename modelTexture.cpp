
#include "modelTexture.h"

// Represent Texture

ModelTexture::ModelTexture() {



}

ModelTexture::ModelTexture(unsigned int id) {

    this->textureID = id;
    this->shineDamper = 1.0f;
    this->reflectivity = 1.0f;
    this->hasTransparency = false;
    this->useFakeLighting = false;

}

unsigned int ModelTexture::getTextureID() {
    return this->textureID;
}
