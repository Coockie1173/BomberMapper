#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>

typedef struct {
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    float yaw;
    float pitch;
    float speed;
    float sensitivity;

    int mouseCaptured; // Flag to track right-click hold state
    mat4 view, projection; 
} Camera;

void camera_init(Camera *camera, vec3 position);
void camera_process_input(Camera *camera, GLFWwindow *window, float deltaTime);
void camera_process_mouse(Camera *camera, double xpos, double ypos);
void camera_update_vectors(Camera *camera);

// NEW: Add function prototypes for callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif // CAMERA_H
