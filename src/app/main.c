#include <stdio.h>
#include <SDL2/SDL.h>
#include "game/camera.h"
#include "render/renderer.h"
#include "platform/window.h"
#include "platform/input.h"
#include "platform/settings.h"
#include "platform/gameState.h"
#include "platform/time.h"
#include "world/world.h"
double time = 0;

int main() {
    initSettings();
    initGameState();
    initInput();
    initCamera();
    initWindow();
    initWorld();
    initRenderer();
    initTimeManager();

    *pGameState = STATE_RUNNING;

    while (*pGameState == STATE_RUNNING)
    {   
        updateTimeManager();
        updateInput();
        updateCamera();
        updateWorld();
        updateRenderer();
        updateWindow();

        time += deltaTime;
        if (time >= 1)
        {
            printf("FPS: %f\n", fps);
            time = 0;
        }
    }

    cleanWorld();
    cleanRenderer();
    cleanWindow();
}