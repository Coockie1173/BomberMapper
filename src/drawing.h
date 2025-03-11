#ifndef DRAWING_H_
#define DRAWING_H_
#include <cglm/cglm.h>
#include <GLFW/glfw3.h>
#include "structs.h"
#include "camera.h"

void drawSquare(vec3 position, vec3 rotation, vec3 scale, vec3 col);
void Render3DWorld(GLFWwindow *window, Camera* camera);
void DrawBorders();

#endif