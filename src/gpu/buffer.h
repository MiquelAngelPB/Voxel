#ifndef buffer_h
#define buffer_h

#include <GL/glew.h>

typedef struct {
    GLuint vao;
    GLuint vbo;
} meshBuffers;

void createMesh(float* vertices, meshBuffers* buffers);
void cleanMesh(meshBuffers* buffers);
void drawMesh(meshBuffers* buffers, int nVertices);

#endif