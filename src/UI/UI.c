#include "UI.h"
#include "FileUI.h"
#include "../camera.h"


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS)
    {
        //get the quadrant
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if(xpos < WIDTH / 2)
        {
            //left half
            if(ypos < HEIGHT / 2)
            {
                //top left quadrant
            }
            else
            {
                //bottom left quadrant
                HandleClicks(xpos, ypos - HEIGHT / 2);
            }
        }
        else
        {
            //right half
            if(ypos < HEIGHT / 2)
            {
                //top right quadrant
            }
            else
            {
                //bottom right quadrant
            }
        }
    }
}