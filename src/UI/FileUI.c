#include <stdio.h>   
#include <stdlib.h> 
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "../camera.h"
#include "FileUI.h"
#include <nfd.h>
#define BUTTONCOUNT 1

struct Button** UIButtons;

void OpenLayerFile()
{
    nfdu8char_t *outPath;
    nfdu8filteritem_t filters[1] = { { "Binary file", "bin" } };
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;

    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY)
    {

        NFD_FreePathU8(outPath);
    }
}

void ConstructFileUI()
{
    UIButtons = malloc(sizeof(struct Button*) * BUTTONCOUNT);

    UIButtons[0] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, OpenLayerFile);
    /*UIButtons[1] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[2] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[3] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[4] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[5] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[6] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[7] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[8] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, NULL);
    UIButtons[9] = MakeButton("./Resources/Open.bmp", (vec2){0,0}, PrintMa);*/
}

void RenderFileUI()
{
    glDisable(GL_BLEND); 
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH / 2, HEIGHT / 2, 0.0f, -1.0f, 1.0f);  // 2D Orthographic projection

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f); 
        glVertex2f(WIDTH, 0.0f); 
        glVertex2f(WIDTH, HEIGHT);  
        glVertex2f(0.0f, HEIGHT); 
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

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DestroyFileUI()
{
    for(int i = 0; i < BUTTONCOUNT; i++)
    {
        DeleteButton(UIButtons[i]);
    }

    free(UIButtons);
}

void HandleClicks(float X, float Y)
{
    for(int i = 0; i < BUTTONCOUNT; i++)
    {
        CheckClick(UIButtons[i], X, Y);
    }
}