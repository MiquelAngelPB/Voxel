#ifndef buffer_h
#define buffer_h

#include <GL/glew.h>

typedef struct {
    GLuint vao;
    GLuint vbo;
} meshBuffers;

//meshes
void createMesh(float* vertices, int nVertices, meshBuffers* buffers);
void cleanMesh(meshBuffers* buffers);
void useMesh(meshBuffers* buffers);
void drawMesh(meshBuffers* buffers, int nVertices);

//general purpose buffers (SSBOs)
void createBuffer(int size, int slot, GLuint* buffer);
void writeBuffer(int size, int slot, GLuint* buffer, void* data);
void cleanBuffer(int size, int slot, GLuint* buffer);

#endif