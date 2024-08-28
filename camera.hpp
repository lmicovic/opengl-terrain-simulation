#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include "math.hpp"

#include "window.h"
#include "Terrain.hpp"

class Camera {



public:

     GLFWwindow* window;

     // Used to Calcualte View Matrix
     glm::vec3 position = glm::vec3(0.0f, 4.0f, -2.0f);             // Camera position
     glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);          // Camera Vector that Point to The From of the Camera
     glm::vec3 cameraUP = glm::vec3(0.0f, 1.0f, 0.0f);              // Camera Vector that Point to Up of The Camera

     // Used to Calculate Camera Angle
     float yaw = -90.0f;                // How Left or Right is Camera
     float pitch = 0.0f;;               // How High or Low Camera is Aimed
     float roll;                        // How Camera is Titlted on Some side

     const float cameraSpeed = 2.0f;


     Camera(GLFWwindow* window) {

        this->window = window;

     }


     // Move Camera Round
     void move(Terrain terrain) {

        float cameraPosX = this->position.x;
        float cameraPosZ = this->position.z;

        // Find Terrain Height on Current Camera Position
        float cameraY = terrain.getHeightOfTerrain(cameraPosX, cameraPosZ, terrain.heights) + 5.0f;

        // Test Camera Terrain Coallision
        if(this->position.y <= cameraY) {
            this->position.y = cameraY;
        }



        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            this->position += this->cameraFront * cameraSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            /*
                Cross Product daje Vektor koji je prav u odnosu na Dva Vektora koja se Mnoze.
                Tako dobijamo X koja se stalno menja u zavisnosti od pozicije CemeraFrom i CameraUp.
            */
            this->position -= glm::normalize(glm::cross(this->cameraFront, this->cameraUP)) * cameraSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            /*
                Cross Product daje Vektor koji je prav u odnosu na Dva Vektora koja se Mnoze.
                Tako dobijamo X koja se stalno menja u zavisnosti od pozicije CemeraFrom i CameraUp.
            */
            this->position += glm::normalize(glm::cross(this->cameraFront, this->cameraUP)) * cameraSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            this->position -= cameraSpeed * this->cameraFront;
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            this->position += cameraSpeed * this->cameraUP;
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            this->position -= cameraSpeed * this->cameraUP;
        }

     }




};

#endif // CAMERA_H
