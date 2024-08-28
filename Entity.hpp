#ifndef ENTITY_H
#define ENTITY_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "TextureModel.h"


// Instance of TexturedModel, has position, rotateion and scale of Textured Model
class Entity {

public:


    TexturedModel texturedModel = TexturedModel();
    glm::vec3 position;
    float rotX, rotY, rotZ;
    float scale;

    Entity(TexturedModel texturedModel, glm::vec3 position, float rotX, float rotY, float rotZ, float scale) {

        this->texturedModel = texturedModel;
        this->position = position;
        this->rotX = rotX;
        this->rotY = rotY;
        this->rotZ = rotZ;
        this->scale = scale;

    }

    // Move Enrity in our Worl
    void inceasePosition(float dx, float dy, float dz) {
        this->position.x += dx;
        this->position.y += dy;
        this->position.z += dz;
    }

    void inceaseRotation(float dx, float dy, float dz) {
        this->rotX += dx;
        this->rotY += dy;
        this->rotZ += dz;
    }

};


#endif // ENTITY_H


