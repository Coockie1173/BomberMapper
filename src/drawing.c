#include "drawing.h"
#include "camera.h"

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

void Render3DWorld(GLFWwindow *window, Camera* camera)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix(); // Save the current matrix state

    // Create View and Projection Matrices
    glm_mat4_identity(camera->view);
    vec3 target;
    glm_vec3_add(camera->position, camera->front, target);
    glm_lookat(camera->position, target, camera->up, camera->view);

    glm_mat4_identity(camera->projection);
    glm_perspective(glm_rad(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f, camera->projection);

    // Load Matrices to OpenGL (Fixed Function)
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((const float *)camera->projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf((const float *)camera->view);

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
    
    glPopMatrix(); // Save the current matrix state
}

void DrawBorders() {
    // Switch to 2D orthogonal projection for border drawing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, -1.0f, 1.0f);  // 2D Orthographic projection
    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(3.0f);  // Set the width of the lines for the borders
    glColor3f(1.0f, 1.0f, 1.0f);  // Set border color (white)

    // Draw borders around each quadrant
    glBegin(GL_LINES);


    // Bottom-left quadrant borders
    glVertex2f(0.0f, HEIGHT / 2);
    glVertex2f(WIDTH / 2, HEIGHT / 2);  // Bottom border
    glVertex2f(WIDTH / 2, HEIGHT / 2);
    glVertex2f(WIDTH / 2, 0.0f);  // Right border

    // Bottom-right quadrant borders
    glVertex2f(WIDTH / 2, HEIGHT / 2);
    glVertex2f(WIDTH, HEIGHT / 2);  // Bottom border
    glVertex2f(WIDTH, HEIGHT / 2);
    glVertex2f(WIDTH, 0.0f);  // Right border

    // Bottom-left quadrant borders
    glVertex2f(0.0f, HEIGHT);
    glVertex2f(WIDTH / 2, HEIGHT);  // Bottom border
    glVertex2f(WIDTH / 2, HEIGHT);
    glVertex2f(WIDTH / 2, 0.0f);  // Right border

    // Bottom-right quadrant borders
    glVertex2f(WIDTH / 2, HEIGHT);
    glVertex2f(WIDTH, HEIGHT); // Bottom border
    glVertex2f(WIDTH, HEIGHT);
    glVertex2f(WIDTH, 0.0f);  // Right border

    glEnd();
}