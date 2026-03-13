#include <stdio.h>
#include <SDL2/SDL.h>
#include "game/camera.h"
#include "render/renderer.h"
#include "platform/window.h"
#include "platform/input.h"
#include "platform/settings.h"
#include "platform/gameState.h"
#include "platform/time.h"

int main() {
    initSettings();
    initGameState();
    initInput();
    initCamera();
    initWindow();
    initRenderer();
    initTimeManager();

    *pGameState = STATE_RUNNING; //everything set up

    while (*pGameState == STATE_RUNNING)
    {   
        updateTimeManager();
        updateInput();
        updateCamera();
        updateRenderer();
        updateWindow();
    }

    cleanRenderer();
    cleanWindow();
}