#include <math.h>
#include "gl_manager.h"
#include "utilities.h"
#include "vector.h"

#ifndef M_PI
#define  M_PI  3.1415926535897932384626433
#endif

struct Camera{
    Vector3 pos;
    Vector3 rot;
};

struct Camera mainCamera = {
    {0, 0, -3},
    {0, 0, 0 }
};

const float rotationXOffset = 0.2;
float minRotationX = -(M_PI / 2.0f) + rotationXOffset;
float maxRotationX = M_PI / 2.0f - rotationXOffset;



void moveCamera(float dx, float dy, float dz) 
{
    float cosY = cosf(mainCamera.rot.y);
    float sinY = sinf(mainCamera.rot.y);

    float forwDirX = dz * sinY;
    float forwDirZ = dz * cosY;

    float sideDirX = dx * cosY;
    float sideDirZ = -dx * sinY;

    mainCamera.pos.x += forwDirX + sideDirX;
    mainCamera.pos.z += forwDirZ + sideDirZ;
    mainCamera.pos.y += dy;
}

void rotateCamera(float dx, float dy, float dz) 
{
    mainCamera.rot.x += dx;
    mainCamera.rot.y += dy;
    if (mainCamera.rot.y < 0) { mainCamera.rot.y += 2 * M_PI; }
    else if (mainCamera.rot.y > 2 * M_PI) { mainCamera.rot.y -= 2 * M_PI; }
    
    if      (mainCamera.rot.x < minRotationX) { mainCamera.rot.x = minRotationX; }
    else if (mainCamera.rot.x > maxRotationX) { mainCamera.rot.x = maxRotationX; }
}

void getCameraPosition(float* x, float* y, float* z) 
{
    *x = mainCamera.pos.x;
    *y = mainCamera.pos.y;
    *z = mainCamera.pos.z;
}

void getCameraRotation(float* rx, float* ry, float* rz) 
{
    *rx = mainCamera.rot.x;
    *ry = mainCamera.rot.y;
    *rz = mainCamera.rot.z;
}

Vector3 getCameraForward()
{
    //Multiply by cos(pitch) to scale the forward vector, so that it doesn't get 
    //longer when looking in a vertical direction
    Vector3 forward;
    forward.x = sin(mainCamera.rot.y) * cos(mainCamera.rot.x);
    forward.y = sin(mainCamera.rot.x);
    forward.z = cos(mainCamera.rot.y) * cos(mainCamera.rot.x);
    return forward;
}
