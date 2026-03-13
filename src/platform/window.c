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
    if (pSettings->debugMode)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    }

    win = SDL_CreateWindow("Voxel Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    80, 60, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);

    glctx = SDL_GL_CreateContext(win);
    glewInit();
    //glViewport(0, 0, pSettings->screenWidth, pSettings->screenHeight);

    if (pSettings->debugMode) { enableGLDebug(); }
    printGLError("initializing OpenGL");
}

void updateWindow()
{
    SDL_GL_SwapWindow(win);
}

void clearScreen()
{
    glClearColor(0, 0.5, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void cleanWindow()
{
    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
}