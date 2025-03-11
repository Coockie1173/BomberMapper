#ifndef FILE_UI_H_
#define FILE_UI_H_
#include "Button.h"

extern struct Button** UIButtons;

void ConstructFileUI();
void RenderFileUI();
void DestroyFileUI();

#endif