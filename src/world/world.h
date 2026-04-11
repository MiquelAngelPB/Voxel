#ifndef world_h
#define world_h

#include "GL/glew.h"
#include "core/vector.h"

typedef struct {
    GLuint buffer;
    Vector3 worldOrigin;
    Vector3I gridBounds;
    float voxelSize;
} worldData;

extern worldData* worldP;

void initWorld();
void updateWorld();
void cleanWorld();

#endif