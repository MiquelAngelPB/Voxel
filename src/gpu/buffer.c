#include <stdio.h>
#include <GL/glew.h>
#include "gpu/gpuDebug.h"
#include "gpu/buffer.h"

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