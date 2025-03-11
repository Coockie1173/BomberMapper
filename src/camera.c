#include "camera.h"

static float lastX = 400, lastY = 300;
static int firstMouse = 1;
static Camera *activeCamera = NULL; // Track the active camera instance

int WIDTH = 800;
int HEIGHT = 600;

void camera_init(Camera *camera, vec3 position) {
    glm_vec3_copy(position, camera->position);
    
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, camera->front);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, camera->worldUp);

    camera->yaw = -90.0f;
    camera->pitch = 0.0f;
    camera->speed = 5.0f;
    camera->sensitivity = 0.1f;
    camera->mouseCaptured = 0;

    activeCamera = camera; // Store reference to active camera

    camera_update_vectors(camera);
}

void camera_process_input(Camera *camera, GLFWwindow *window, float deltaTime) {
    float velocity = camera->speed * deltaTime;
    vec3 movement;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glm_vec3_scale(camera->front, velocity, movement);
        glm_vec3_add(camera->position, movement, camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        glm_vec3_scale(camera->front, velocity, movement);
        glm_vec3_sub(camera->position, movement, camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glm_vec3_scale(camera->right, velocity, movement);
        glm_vec3_sub(camera->position, movement, camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm_vec3_scale(camera->right, velocity, movement);
        glm_vec3_add(camera->position, movement, camera->position);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera->mouseCaptured = 1;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
        camera->mouseCaptured = 0;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void camera_process_mouse(Camera *camera, double xpos, double ypos) {
    if (!camera->mouseCaptured) return;

    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = 0;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;
    lastX = (float)xpos;
    lastY = (float)ypos;

    xoffset *= camera->sensitivity;
    yoffset *= camera->sensitivity;

    camera->yaw += xoffset;
    camera->pitch += yoffset;

    if (camera->pitch > 89.0f) camera->pitch = 89.0f;
    if (camera->pitch < -89.0f) camera->pitch = -89.0f;

    camera_update_vectors(camera);
}

void camera_update_vectors(Camera *camera) {
    vec3 front;
    front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    front[1] = sin(glm_rad(camera->pitch));
    front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));

    glm_vec3_normalize_to(front, camera->front);
    
    glm_vec3_cross(camera->front, camera->worldUp, camera->right);
    glm_vec3_normalize(camera->right);

    glm_vec3_cross(camera->right, camera->front, camera->up);
    glm_vec3_normalize(camera->up);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (activeCamera != NULL) {
        camera_process_mouse(activeCamera, xpos, ypos);
    }
}
