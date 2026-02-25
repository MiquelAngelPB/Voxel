#include <math.h>
#include "gl_manager.h"
#include "utilities.h"
#include "vector.h"

#ifndef M_PI
#define  M_PI  3.1415926535897932384626433
#endif

typedef struct{
    Vector3 pos;
    Vector3 rot;
    Vector3 v;
    Vector3 a;
} Camera;

Camera mainCamera = {
    {0, 0, -3},
    {0, 0, 0 },
    {0, 0, 0 },
    {0, 0, 0 }
};

const float rotationXOffset = 0.2;
float minRotationX = -(M_PI / 2.0f) + rotationXOffset;
float maxRotationX = M_PI / 2.0f - rotationXOffset;

float speed = 0.01f;
float maxSpeed = 30;
float friction = 0.95f;

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

void updateCameraPos()
{
    mainCamera.v.x += mainCamera.a.x * speed;
    mainCamera.v.y += mainCamera.a.y * speed;
    mainCamera.v.z += mainCamera.a.z * speed;

    moveCamera(mainCamera.v.x, mainCamera.v.y, mainCamera.v.z);

    mainCamera.v.x *= friction;
    mainCamera.v.y *= friction;
    mainCamera.v.z *= friction;

    //TODO: Refactor this
    if (mainCamera.v.x > maxSpeed) { mainCamera.v.x = maxSpeed; }
    else if (mainCamera.v.x < -maxSpeed) { mainCamera.v.x = -maxSpeed; }
    if (mainCamera.v.y > maxSpeed) { mainCamera.v.y = maxSpeed; }
    else if (mainCamera.v.y < -maxSpeed) { mainCamera.v.y = -maxSpeed; }
    if (mainCamera.v.x > maxSpeed) { mainCamera.v.x = maxSpeed; }
    else if (mainCamera.v.z < -maxSpeed) { mainCamera.v.z = -maxSpeed; }
}

void pushCamera(float ax, float ay, float az) 
{
    mainCamera.a.x = ax;
    mainCamera.a.y = ay;
    mainCamera.a.z = az;
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

Camera* getCameraTransform() {
    return &mainCamera;
}