#ifndef window_h
#define window_h

#include <SDL2/SDL.h>

extern SDL_Window* win;

void initWindow();
void updateWindow();
void cleanWindow();
void clearScreen();

#endif