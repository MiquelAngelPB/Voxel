#include <GL/glew.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "gl_manager.h"
#include "camera.h"
#include "input.h"

bool quit;

int main() {
    glManager_Init();
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
    glManager_Clean();
}