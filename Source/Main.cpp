#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <iostream>
#include <vector>

#include "../Header/Util.h"
#include "../Header/Aquarium.h"
#include <thread>


const int FPS = 75;

void limitFPS(double& lastTimeForRefresh)
{
    double now = glfwGetTime();
    double targetFrameTime = 1.0 / FPS;
    double remaining = (lastTimeForRefresh + targetFrameTime) - now;

    if (remaining > 0.0)
    {
        std::this_thread::sleep_for(std::chrono::duration<double>(remaining));
    }
    

    lastTimeForRefresh = glfwGetTime();
}



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Akvarijum", primary, NULL);

    if (window == NULL) return endProgram("Prozor nije uspeo da se kreira.");
    glfwMakeContextCurrent(window);


    GLFWcursor* cursor = loadImageToCursor("res/cursor.png");

    glfwSetCursor(window, cursor);


    if (glewInit() != GLEW_OK) return endProgram("GLEW nije uspeo da se inicijalizuje.");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    float wallWidth = 10.0f / (mode->width / 2.0f);


    Aquarium aquarium(window, wallWidth);

    if (!aquarium.initialize()) {
        std::cerr << "Failed to initialize aquarium" << std::endl;
        return -1;
    }
    glfwSetWindowUserPointer(window, &aquarium);
    glfwSetKeyCallback(window, Aquarium::keyCallback);

    


    glClearColor(0.5f, 0.8f, 1.00f, 1.0f);
    double lastTimeForRefresh = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        aquarium.run();
        

        glfwSwapBuffers(window);
        limitFPS(lastTimeForRefresh);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}