#ifndef player_h
#define player_h

#include "vector.h"

typedef struct{
    Vector3 pos;
    Vector3 rot;
    Vector3 v;
    Vector3 a;
} Camera;

extern Camera mainCamera;

void moveCamera(float dx, float dy, float dz);
void rotateCamera(float dx, float dy, float dz);
void pushCamera(float ax, float ay, float az);

void getCameraPosition(float* x, float* y, float* z);
void getCameraRotation(float* rx, float* ry, float* rz);
Vector3 getCameraForward();
Camera* getCameraTransform();

void updateCameraPos();

#endif