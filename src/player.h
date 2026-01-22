#ifndef player_h
#define player_h

extern struct Camera mainCamera;
void moveCamera(float dx, float dy, float dz);
void rotateCamera(float dx, float dy, float dz);
void getCameraPosition(float* x, float* y, float* z);
void getCameraRotation(float* rx, float* ry, float* rz);

#endif