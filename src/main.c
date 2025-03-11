#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>   
#include <stdlib.h> 

#include "UI/FileUI.h" 

#include "structs.h"
#include "drawing.h"
#include "main.h"
#include "camera.h"
#include "macros.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Window dimensions

Camera camera;

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Basic GLFW Window", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowSizeLimits(window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    vec3 startPos = {0.0f, 0.0f, 3.0f};
    camera_init(&camera, startPos);

    ConstructFileUI();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera_process_input(&camera, window, deltaTime);

        // Set the viewport for the top-left quadrant (x: 0, y: 0, width: WIDTH/2, height: HEIGHT/2)
        glViewport(0, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
        Render3DWorld(window, &camera);  // Render only in the top-left quadrant

        // Optionally render other content in the other three quadrants
        // Bottom-left quadrant
        glViewport(0, 0, WIDTH / 2, HEIGHT / 2);
        // Render other content if needed
        RenderFileUI();
        
        // Top-right quadrant
        glViewport(WIDTH / 2, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
        // Render other content if needed

        // Bottom-right quadrant
        glViewport(WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2);
        // Render other content if needed

        DrawBorders();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    DestroyFileUI();

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

