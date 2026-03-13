#include <stdio.h>
#include <GL/glew.h>

void printGLError(char* context)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("OpenGL error when %s: %d\n", context, error);
    }
}