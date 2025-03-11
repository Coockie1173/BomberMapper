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
const int WIDTH = 800;
const int HEIGHT = 600;

struct WorldSquare* TempTiles;

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

    TempTiles = malloc(sizeof(struct WorldSquare) * 64 * 64 * 64);

    const int MapX = 4;
    const int MapY = 4;
    const int MapZ = 1;

    for(int z = 0; z < MapZ; z++)
    {
        for(int y = 0; y < MapY; y++)
        {
            for(int x = 0; x < MapX; x++)
            {
                int idx = x + (y * MapX) + (z * MapY * MapX);
                TempTiles[idx].Col = (struct Colour){(float)x / MapX, (float)y / MapY, 1};
                TempTiles[idx].Layer = z * 1;
                TempTiles[idx].PosX = x * 1;
                TempTiles[idx].PosY = y * 1;
                TempTiles[idx].Size = 1;
                printf("Generating tile %d\n", idx);
            }
        }
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
        // Set background color and clear screen

        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera_process_input(&camera, window, deltaTime);

        Render(window);
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();

    free(TempTiles);

    return 0;
}

void Render(GLFWwindow *window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    // Swap buffers and poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
}
