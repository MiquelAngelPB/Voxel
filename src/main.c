//Implement this: https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html
//Also: https://www.youtube.com/watch?v=wg4om77Drr0
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <stdio.h>

//variables
SDL_Window* win = NULL;
SDL_GLContext glctx = NULL;

//methods
void initSDL_GL();
void cleanSDL_GL();
void testGL();

//main()
int main() {
    initSDL_GL();

    testGL();
    SDL_Delay(2000);

    cleanSDL_GL();
}

void cleanSDL_GL()
{
    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void initSDL_GL()
{
    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Voxel Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600, SDL_WINDOW_OPENGL);
    glctx = SDL_GL_CreateContext(win);

    SDL_GL_SetAttribute(GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(GL_DEPTH_BUFFER_BIT, 24);
}

void testGL()
{
  // Set every pixel in the frame buffer to the current clear color.
  glClear(GL_COLOR_BUFFER_BIT);

  // Drawing is done by specifying a sequence of vertices.  The way these
  // vertices are connected (or not connected) depends on the argument to
  // glBegin.  GL_POLYGON constructs a filled polygon.
  glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(-0.6, -0.75, 0.5);
    glColor3f(0, 1, 0); glVertex3f(0.6, -0.75, 0);
    glColor3f(0, 0, 1); glVertex3f(0, 0.75, 0);
  glEnd();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
}