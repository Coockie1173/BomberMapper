#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>   
#include <stdlib.h> 
 
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return -1;
    }

    vec3 startPos = {0.0f, 0.0f, 3.0f};
    camera_init(&camera, startPos);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera_process_input(&camera, window, deltaTime);

        // Set the viewport for the top-left quadrant (x: 0, y: 0, width: WIDTH/2, height: HEIGHT/2)
        glViewport(0, HEIGHT / 2, WIDTH / 2, HEIGHT / 2);
        Render3DWorld(window);  // Render only in the top-left quadrant

        // Optionally render other content in the other three quadrants
        // Bottom-left quadrant
        glViewport(0, 0, WIDTH / 2, HEIGHT / 2);
        // Render other content if needed
        
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

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void Render3DWorld(GLFWwindow *window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix(); // Save the current matrix state

    // Create View and Projection Matrices
    glm_mat4_identity(camera.view);
    vec3 target;
    glm_vec3_add(camera.position, camera.front, target);
    glm_lookat(camera.position, target, camera.up, camera.view);

    glm_mat4_identity(camera.projection);
    glm_perspective(glm_rad(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f, camera.projection);

    // Load Matrices to OpenGL (Fixed Function)
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((const float *)camera.projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf((const float *)camera.view);

    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            for (int z = -3; z < 1; z++)
            {
                vec3 Pos = {x, z, y};
                vec3 rot = {0.0f, 0.0f, 0.0f};
                vec3 scale = {1.0f, 1.0f, 1.0f};
                vec3 Col = {(float)x / 10, 0, (float)y / 10};
                drawSquare(Pos, rot, scale, Col);
            }
        }
    }
    
    glPopMatrix(); // Save the current matrix state
}

void DrawBorders() {
    // Switch to 2D orthogonal projection for border drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);  // 2D Orthographic projection
    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(3.0f);  // Set the width of the lines for the borders
    glColor3f(1.0f, 1.0f, 1.0f);  // Set border color (white)

    // Draw borders around each quadrant
    glBegin(GL_LINES);


    // Bottom-left quadrant borders
    glVertex2f(0.0f, HEIGHT / 2);
    glVertex2f(WIDTH / 2, HEIGHT / 2);  // Bottom border
    glVertex2f(WIDTH / 2, HEIGHT / 2);
    glVertex2f(WIDTH / 2, 0.0f);  // Right border

    // Bottom-right quadrant borders
    glVertex2f(WIDTH / 2, HEIGHT / 2);
    glVertex2f(WIDTH, HEIGHT / 2);  // Bottom border
    glVertex2f(WIDTH, HEIGHT / 2);
    glVertex2f(WIDTH, 0.0f);  // Right border

    // Bottom-left quadrant borders
    glVertex2f(0.0f, HEIGHT);
    glVertex2f(WIDTH / 2, HEIGHT);  // Bottom border
    glVertex2f(WIDTH / 2, HEIGHT);
    glVertex2f(WIDTH / 2, 0.0f);  // Right border

    // Bottom-right quadrant borders
    glVertex2f(WIDTH / 2, HEIGHT);
    glVertex2f(WIDTH, HEIGHT); // Bottom border
    glVertex2f(WIDTH, HEIGHT);
    glVertex2f(WIDTH, 0.0f);  // Right border

    glEnd();
}