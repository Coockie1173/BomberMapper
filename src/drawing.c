#include "drawing.h"

void drawSquare(vec3 position, vec3 rotation, vec3 scale, vec3 col) 
{
    glPushMatrix(); // Save the current matrix state

    // Apply TRS transformations
    glTranslatef(position[0], position[1], position[2]); // Translation
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f); // Rotation around X
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f); // Rotation around Y
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f); // Rotation around Z
    glScalef(scale[0], scale[1], scale[2]); // Scaling

    // Draw the square
    glBegin(GL_QUADS);
        glColor4f(col[0], col[1], col[2], 0.5f); glVertex3f(-0.5f, 0.0f, -0.5f);
        glColor4f(col[0], col[1], col[2], 0.5f); glVertex3f( 0.5f, 0.0f, -0.5f);
        glColor4f(col[0], col[1], col[2], 0.5f); glVertex3f( 0.5f, 0.0f,  0.5f);
        glColor4f(col[0], col[1], col[2], 0.5f); glVertex3f(-0.5f, 0.0f,  0.5f);
    glEnd();

    glPopMatrix(); // Restore the previous matrix state
}