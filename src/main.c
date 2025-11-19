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
void createScreenMesh();

//main()
int main() {
    initSDL_GL();

    createScreenMesh();
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

    SDL_GL_SetAttribute(GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(GL_DEPTH_BUFFER_BIT, 24);
    glctx = SDL_GL_CreateContext(win);
}

void createScreenMesh()
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_TRIANGLES);

      //Triangle 1
      glColor3f(1, 0, 0); glVertex2f(-1.0f, -1.0f);
      glColor3f(0, 1, 0); glVertex2f( 1.0f, -1.0f);
      glColor3f(0, 0, 1); glVertex2f( 1.0f,  1.0f);

      //Triangle 2
      glColor3f(1, 0, 1); glVertex2f(-1.0f, -1.0f);
      glColor3f(1, 1, 0); glVertex2f( 1.0f,  1.0f);
      glColor3f(0, 1, 1); glVertex2f(-1.0f,  1.0f);
  
      glEnd();

  SDL_GL_SwapWindow(win);
}