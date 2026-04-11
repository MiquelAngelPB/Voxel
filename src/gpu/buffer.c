#include <stdio.h>
#include <GL/glew.h>
#include "gpu/gpuDebug.h"
#include "gpu/buffer.h"

//MESHES ============================

void createMesh(float* vertices, int nVertices, meshBuffers* buffers)
{
    //Each triangle is 2D, so 2 floats per vertex
    //Coordinates range from 0, 0 (bottom left) to 1, 1 (top right)

    glGenVertexArrays(1, &buffers->vao);
    glGenBuffers(1, &buffers->vbo);

    glBindVertexArray(buffers->vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffers->vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * nVertices, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    printGLError("creating mesh");
}

void cleanMesh(meshBuffers* buffers)
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &buffers->vbo);
    glDeleteVertexArrays(1, &buffers->vao);
    printGLError("cleaning mesh");
}

void useMesh(meshBuffers* buffers)
{
    glBindVertexArray(buffers->vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffers->vbo);
}

void drawMesh(meshBuffers* buffers, int nVertices)
{
    glDrawArrays(GL_TRIANGLES, 0, nVertices);
}

//GENERIC BUFFERS (SSBOs) ==========================

void createBuffer(int size, int slot, GLuint* buffer)
{
    glCreateBuffers(1, buffer);
    glNamedBufferData(*buffer, size, NULL, GL_STREAM_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, *buffer);
}

void writeBuffer(int size, int slot, GLuint* buffer, void* data)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, *buffer);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, size, data);
}

void cleanBuffer(int size, int slot, GLuint* buffer)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, slot, 0);
    glDeleteBuffers(1, buffer);
}