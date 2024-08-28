
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

/*
    Represent Light
*/
class Light {

public:

    glm::vec3 position;         // Light Position
    glm::vec3 color;            // Light Color(R,G,B)
    glm::vec3 lightDistance;    // Attenuacija

    Light();
    Light(glm::vec3 position, glm::vec3 color, glm::vec3 lightDistance);


};

#endif // LIGHT_H
