#ifndef cmaera_h
#define camera_h

#include "core/vector.h"
#include "platform/input.h"
#include "platform/settings.h"

typedef struct{
    Vector3 pos;
    Vector3 rot;
    Vector3 v;
    Vector3 a;
    Vector3 forward;
} Camera;

extern Camera* pCamera;
void initCamera();

void moveCamera(Vector3 movement);
void rotateCamera(Vector3 rotation);
void pushCamera(Vector3 acceleration);

void getCameraPosition(float* x, float* y, float* z);
void getCameraRotation(float* rx, float* ry, float* rz);
Vector3 getCameraForward();
Camera* getCameraTransform();

void updateCamera();

#endif