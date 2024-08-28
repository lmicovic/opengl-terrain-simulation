#ifndef PROCESINPUT_H
#define PROCESINPUT_H

#include <GLFW/glfw3.h>
#include "camera.hpp"

void processInput(GLFWwindow *window, Camera* camera);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);




#endif // PROCESINPUT_H
