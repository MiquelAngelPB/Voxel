#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "platform/window.h"
#include "platform/settings.h"
#include "gpu/gpuDebug.h"

SDL_Window* win = NULL;
SDL_GLContext glctx = NULL;

void initWindow()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GL_SetAttribute(GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    win = SDL_CreateWindow("Voxel Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    pSettings->screenWidth, pSettings->screenHeight, SDL_WINDOW_OPENGL);

    glctx = SDL_GL_CreateContext(win);
    glewInit();

    printGLError("initializing OpenGL");
}

void updateWindow()
{
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(win);
}

void cleanWindow()
{
    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
}