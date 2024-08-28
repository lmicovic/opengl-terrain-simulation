#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window {

public:

    const int WIDTH = 1200;
    const int HEIGHT = 800;

    Window();
    GLFWwindow* createWindow();



};

#endif // WINDOW_H

