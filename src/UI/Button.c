#include "Button.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "../camera.h"


struct Button* MakeButton(const char* FileName, vec2 Position, void* OnClickFunction)
{
    struct Button* B = malloc(sizeof(struct Button));

    int width, height, nrChannels;
    unsigned char *data = stbi_load(FileName, &width, &height, &nrChannels, 0);

    if(!data)
    {
        return 0;
    }

    GLuint Texture;
    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);

    B->OnClick = OnClickFunction;
    B->Size[0] = width;
    B->Size[1] = height;
    B->TextureID = Texture;
    B->Position[0] = Position[0];
    B->Position[1] = Position[1];

    return B;
}

void RenderButton(const struct Button* But)
{
    glBindTexture(GL_TEXTURE_2D, But->TextureID);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(But->Position[0], But->Position[1]);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(But->Position[0] + But->Size[0], But->Position[1]);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(But->Position[0] + But->Size[0], But->Position[1] + But->Size[1]);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(But->Position[0], But->Position[1] + But->Size[1]);
    glEnd();
}

void DeleteButton(struct Button* But)
{
    glDeleteTextures(1, &But->TextureID);

    free(But);
}

void CheckClick(struct Button* But, float X, float Y)
{
    if(But->OnClick == NULL)
    {
        return;
    }
    //this assumes you've corrected for the quadrant
    if(But->Position[0] < X && But->Position[0] + But->Size[0] > X)
    {
        if(But->Position[1] < Y && But->Position[1] + But->Size[1] > Y)
        {
            But->OnClick();
        }
    }
}