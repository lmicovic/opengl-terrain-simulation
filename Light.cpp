#include "Light.hpp"

Light::Light() {

}

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 lightDistance) {

    this->position = position;
    this->color = color;
    this->lightDistance = lightDistance;

}
