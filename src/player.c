#include <math.h>
#include "gl_manager.h"

struct Camera{
    float x;
    float y;
    float z;

    float rx;
    float ry;
    float rz;
};

struct Camera mainCamera = {
    0, 0, 0,
    0, 0, 0
};

void moveCamera(float dx, float dy, float dz) 
{
    float cosY = cosf(mainCamera.ry);
    float sinY = sinf(mainCamera.ry);

    float forwDirX = dz * sinY;
    float forwDirZ = dz * cosY;

    float sideDirX = dx * cosY;
    float sideDirZ = -dx * sinY;

    mainCamera.x += forwDirX + sideDirX;
    mainCamera.z += forwDirZ + sideDirZ;
    mainCamera.y += dy;
}

void rotateCamera(float dx, float dy, float dz) 
{
    mainCamera.rx += dx;
    mainCamera.ry += dy;
    mainCamera.rz += dz;
}

void getCameraPosition(float* x, float* y, float* z) 
{
    *x = mainCamera.x;
    *y = mainCamera.y;
    *z = mainCamera.z;
}

void getCameraRotation(float* rx, float* ry, float* rz) 
{
    *rx = mainCamera.rx;
    *ry = mainCamera.ry;
    *rz = mainCamera.rz;
}
