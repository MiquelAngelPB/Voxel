#include <GL/glew.h>
#include <stdio.h>
#include <stdbool.h>

#include "gl_manager.h"
#include "camera.h"
#include "input.h"

bool quit;

int main() {
    glManager_Init();

    while (!quit)
    {
        manageInput();
        updateCameraPos();
        glManager_Render();
    }
    
    //SDL_Delay(3000);
    glManager_Clean();
}