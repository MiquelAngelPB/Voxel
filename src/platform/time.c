#include <SDL2/SDL.h>

double fps;
double deltaTime;
double frequency;
Uint64 prevTime;
Uint64 thisTime;

void initTimeManager()
{
    frequency = (double)SDL_GetPerformanceFrequency();
    prevTime = 0;
    thisTime = SDL_GetPerformanceCounter();
}

void updateTimeManager()
{
    prevTime = thisTime;
    thisTime = SDL_GetPerformanceCounter();
    deltaTime = (double)(((thisTime - prevTime) * 1000 / frequency) * 0.001);
    fps = 1.0 / deltaTime;
}