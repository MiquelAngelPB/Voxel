//Implement this: https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html
//Also: https://www.youtube.com/watch?v=wg4om77Drr0
#include <SDL2/SDL.h>
//#include <GL/gl.h>
#include <GL/glew.h>
#include <stdio.h>
#include "gl_manager.h"

//variables

//methods

//main()
int main() {
    glManager_Init();
    //TODO: main loop here.
    glManager_Render();
    SDL_Delay(3000);
    glManager_Clean();
}