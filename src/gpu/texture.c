#include <GL/glew.h>
#include "gpu/gpuDebug.h"

GLuint createTexture(int width, int height)
{
    GLuint texture;
    float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    glCreateTextures(GL_TEXTURE_2D, 1, &texture);

    glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTextureParameterfv(texture, GL_TEXTURE_BORDER_COLOR, borderColor);  

    glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
    printGLError("creating texture");

    return texture;
}

void cleanTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
    texture = 0;
}

void bindImageTexture(GLuint texture, int slot)
{
    glBindImageTexture(slot, texture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
}

void bindSampleTexture(GLuint texture, int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);
}