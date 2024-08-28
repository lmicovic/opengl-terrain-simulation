
#ifndef PROCESINPUT_H

#include <glad/glad.h>
#include "processInput.hpp"

const float cameraSpeed = 2.0f;
Camera* camera2 = NULL;

void processInput(GLFWwindow *window, Camera* camera)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//        camera->position += camera->cameraFront * cameraSpeed;
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//        camera->position -= glm::normalize(glm::cross(camera->cameraFront, camera->cameraUP)) * cameraSpeed;
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//        camera->position += glm::normalize(glm::cross(camera->cameraFront, camera->cameraUP)) * cameraSpeed;
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//        camera->position -= cameraSpeed * camera->cameraFront;
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        camera->position += cameraSpeed * camera->cameraUP;
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
//        camera->position -= cameraSpeed * camera->cameraUP;
//    }


}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


#endif // PROCESINPUT_H
