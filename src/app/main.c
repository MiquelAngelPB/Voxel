#include <stdio.h>

#include "game/camera.h"
#include "render/renderer.h"
#include "platform/window.h"
#include "platform/input.h"
#include "platform/settings.h"
#include "platform/gameState.h"

int main() {
    initSettings();
    initGameState();
    initInput();
    initCamera();
    initWindow();
    initRenderer();

    int tmp = 0;
    *pGameState = STATE_RUNNING; //everything set up

    while (*pGameState == STATE_RUNNING)
    {
        updateInput();
        updateCamera();
        updateRenderer();
        updateWindow();

        float x, y, z;
        getCameraPosition(&x, &y, &z);
        x = (int)x;
        y = (int)y;
        z = (int)z;
        printf("X: %f Y: %f Z: %f\n", x, y, z);

        /*getCameraRotation(&x, &y, &z);
        x = (int)x;
        y = (int)y;
        z = (int)z;
        printf("rX: %f rY: %f rZ: %f\n", x, y, z);*/
        //system("clear");
    }

    cleanRenderer();
    cleanWindow();
    
    /*glManager_Init();
    int fps = 0;
    int frameCount = 0;
    float elapsedTime = 0.0f;
    float deltaTime = 0.0f;
    float totalTime = 0.0f;

    Uint64 lastCounter = SDL_GetPerformanceCounter();
    Uint64 frequency   = SDL_GetPerformanceFrequency();

    while (!quit)
    {
        manageInput();
        updateCameraPos();
        glManager_Render();

        //TODO: make a proper FPS counter
        Uint64 currentCounter = SDL_GetPerformanceCounter();
        deltaTime = (float)(currentCounter - lastCounter) / (float)frequency;
        lastCounter = currentCounter;

        frameCount++;
        elapsedTime += deltaTime;

        if (elapsedTime >= 1.0f)
        {
            fps = frameCount;
            frameCount = 0;
            elapsedTime = 0.0f;

            char title[64];
            sprintf(title, "Voxel Project - FPS: %d", fps);
            SDL_SetWindowTitle(win, title);
        }
    }
    
    //SDL_Delay(3000);
    glManager_Clean();*/
}