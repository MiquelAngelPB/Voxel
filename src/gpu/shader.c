#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "core/file.h"
#include "gpu/gpuDebug.h"
#include "gpu/shader.h"

//Shaders are organized by programs, for example:
//Physics program: compute shader
//Raymarching program: compute shader
//Rendering program: vertex shader + fragment shader

shaderData loadShader(shaderType type, char* path)
{
    GLuint pShader;
    switch (type)
    {
        case SHADER_VERTEX:
            pShader = glCreateShader(GL_VERTEX_SHADER); break;
        case SHADER_FRAGMENT:
            pShader = glCreateShader(GL_FRAGMENT_SHADER); break;
        case SHADER_COMPUTE:
            pShader = glCreateShader(GL_COMPUTE_SHADER); break;
        default:
            break;
    }

    int error;
    const char* shaderSrc = readFile(path, &error);
    if (error)
    {
        printf("Error reading shader file: %d\n", error);
        return (shaderData){0};
    }

    printGLError("creating shaders");
    return (shaderData){pShader, shaderSrc, type};
}

void setUniform(uniformType type, char* name, void* data, GLuint* pProgram)
{
    GLint uniform = glGetUniformLocation(*pProgram, name);
        if (uniform == -1) {
        printf("Uniform '%s' not found in program %d\n", name, *pProgram);
        return;
    }

    switch (type)
    {
        case UNIFORM_TEXTURE:
            GLint* texture = (GLint*)data;
            glUniform1i(uniform, *texture);
            printGLError("Setting texture uniform");
            break;
        case UNIFORM_V3:
            float* v3 = data;
            glUniform3f(uniform, v3[0], v3[1], v3[2]);
            break;
        case UNIFORM_FLOAT:
            float* f = data;
            glUniform1f(uniform, *f);
            break;
        default:
            break;
    }
}

//Compiles all shaders and links them into a single program.
void compileShaders(shaderData* shaders, int nShaders, GLuint* pProgram)
{
    GLint succes;
    char infoLog[512];

    for (int i = 0; i < nShaders; i++)
    {
        glShaderSource(shaders[i].pShader, 1, &shaders[i].content, NULL);
        glCompileShader(shaders[i].pShader);

        glGetShaderiv(shaders[i].pShader, GL_COMPILE_STATUS, &succes);
        if (!succes)
        {
            glGetShaderInfoLog(shaders[i].pShader, 512, NULL, infoLog);
            printf("Shader Compilation Failed:\n%s\n", infoLog);
            exit(-1);
        }
    }

    *pProgram = glCreateProgram();

    for (int i = 0; i < nShaders; i++)
    {
        glAttachShader(*pProgram, shaders[i].pShader);
    }
    glLinkProgram(*pProgram);
    
    glGetProgramiv(*pProgram, GL_LINK_STATUS, &succes);
    if (!succes)
    {
        glGetProgramInfoLog(*pProgram, 512, NULL, infoLog);
        printf("Linking Failed:\n%s\n", infoLog);
        exit(-1);
    }
}

void useProgram(GLuint program)
{
    glUseProgram(program);
}

void runComputeShader(int x, int y, int z)
{
    glDispatchCompute(x, y, z);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}