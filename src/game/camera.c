#include <math.h>
#include "core/vector.h"
#include "game/camera.h"
#include "platform/input.h"
#include "platform/settings.h"
#include "platform/time.h"

Camera mainCamera;
Camera* pCamera;

const float rotationXOffset = 0.2;
float minRotationX = -(M_PI / 2.0f) + rotationXOffset;
float maxRotationX = M_PI / 2.0f - rotationXOffset;

float speed = 0.2f;
float maxSpeed = 30;
float friction = 0.95f;

void initCamera()
{
    mainCamera = (Camera){
        {0, 0, -3},
        {0, 0, 0 },
        {0, 0, 0 },
        {0, 0, 0 },
        {0, 0, 1 }
    };

    pCamera = &mainCamera;
}

void updateCamera()
{
    if (pInput->hasChanged)
    {
        pushCamera(pInput->keyMovement);
        rotateCamera(multVector3((Vector3){pInput->mouseMovement.x, pInput->mouseMovement.y, 0}, pSettings->sensitivity));
        mainCamera.forward = getCameraForward();
    }

    mainCamera.v.x += mainCamera.a.x * speed * deltaTime;
    mainCamera.v.y += mainCamera.a.y * speed * deltaTime;
    mainCamera.v.z += mainCamera.a.z * speed * deltaTime;

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

    moveCamera(mainCamera.v);
}

void pushCamera(Vector3 acceleration) 
{
    mainCamera.a.x = acceleration.x;
    mainCamera.a.y = acceleration.y;
    mainCamera.a.z = acceleration.z;
}

void moveCamera(Vector3 movement)
{
    float dx, dy, dz;
    dx = movement.x;
    dy = movement.y;
    dz = movement.z;

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

void rotateCamera(Vector3 rotation) 
{
    float dx, dy, dz;
    dx = rotation.x;
    dy = rotation.y;
    //dz = rotation.z; not used for now

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