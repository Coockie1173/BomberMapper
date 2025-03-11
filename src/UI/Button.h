#ifndef BUTTON_H_
#define BUTTON_H_

#include <cglm/cglm.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

struct Button
{
    GLuint TextureID;
    vec2 Size;
    vec2 Position;
    void (*OnClick)();
};

struct Button* MakeButton(const char* FileName, vec2 Position, void* OnClickFunction);
void RenderButton(const struct Button* But);
void DeleteButton(struct Button* But);

//checks for click and runs the function if it's actually clicked
void CheckClick(struct Button* But, float X, float Y);

#endif