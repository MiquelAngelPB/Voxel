#include <stdlib.h>
#include <math.h>
#include "gpu/buffer.h"
#include "core/vector.h"
#include "world.h"

int mapSize = 32;
float voxelSize = 0.3f;
int memorySize;

worldData* worldP;
worldData world = {
    .buffer = (GLuint)0,
    .gridBounds = (Vector3I){0, 0, 0},
    .voxelSize = 0
};

void initWorld()
{
    worldP = &world;
    memorySize = sizeof(int) * mapSize * mapSize * mapSize;
    world.gridBounds = (Vector3I){mapSize, mapSize, mapSize};
    world.voxelSize = voxelSize;

    createBuffer(sizeof(int) * mapSize * mapSize * mapSize, 1, &world.buffer);

    int* tmpWorld = calloc(mapSize * mapSize * mapSize, sizeof(int));
    for(int x = 0; x < mapSize; x++)
    {
        for(int z = 0; z < mapSize; z++)
        {
            int y = (int)floor(sin(z*100)*cos(x*100)*2 + 8);
            int cx = 70;
            int cy = rand() % 256;
            int cz = 0;
            tmpWorld[x + y * mapSize + z * mapSize * mapSize] = cx << 16 | cy << 8 | cz;
        }
    }
    tmpWorld[0] = 255 << 16 | 255 << 8 | 255;
    writeBuffer(sizeof(int) * mapSize * mapSize * mapSize, 1, &world.buffer, tmpWorld);
    free(tmpWorld);
}

void updateWorld()
{

}

void cleanWorld()
{
    cleanBuffer(sizeof(int) * mapSize * mapSize * mapSize, 0, &world.buffer);
}