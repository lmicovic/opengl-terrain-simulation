#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef DISPLAY_H
#define DISPLAY_H



class Display {

public:
    int WIDTH = 1200;
    int HEIGHT = 720;

    GLFWwindow* window;

    Display();
    void createDisplay();
    void updateDisplay();
    void closeDisplay();




};

#endif

