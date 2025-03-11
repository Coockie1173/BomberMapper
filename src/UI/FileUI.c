#include <stdio.h>   
#include <stdlib.h> 
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "../camera.h"
#include "FileUI.h"
#define BUTTONCOUNT 10

struct Button** UIButtons;

void ConstructFileUI()
{
    UIButtons = malloc(sizeof(struct Button*) * BUTTONCOUNT);

    UIButtons[0] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[1] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[2] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[3] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[4] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[5] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[6] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[7] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[8] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[9] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
}

void RenderFileUI()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH / 2, HEIGHT / 2, 0.0f, -1.0f, 1.0f);  // 2D Orthographic projection

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, 0.0f, -5.0f); 
        glVertex3f(WIDTH, 0.0f, -5.0f); 
        glVertex3f(WIDTH, HEIGHT, -5.0f);  
        glVertex3f(0.0f, HEIGHT, -5.0f); 
    glEnd();

    float PosX = 0, PosY = 0;
    for(int i = 0; i < BUTTONCOUNT; i++)
    {
        UIButtons[i]->Position[0] = PosX;
        UIButtons[i]->Position[1] = PosY;
        PosX += UIButtons[i]->Size[0];
        if(PosX > WIDTH / 2.5f)
        {
            PosX = 0;
            PosY += UIButtons[i]->Size[1];
        }
        RenderButton(UIButtons[i]);
    }
}

void DestroyFileUI()
{
    for(int i = 0; i < BUTTONCOUNT; i++)
    {
        DeleteButton(UIButtons[i]);
    }

    free(UIButtons);
}