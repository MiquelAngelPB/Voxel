#ifndef gl_manager
#define gl_manager

#include <SDL2/SDL.h>
extern SDL_Window* win;

void glManager_Init();
void glManager_SetCamPos(float x, float y, float z);
void glManager_SetCamRot(float rx, float ry, float rz);
void glManager_Render();
void glManager_Clean();

#endif