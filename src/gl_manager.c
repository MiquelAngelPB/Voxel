#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include "utilities.h"
#include "player.h"
#include "vector.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//variables
SDL_Window* win = NULL;
SDL_GLContext glctx = NULL;
GLuint vao = 0;
GLuint vbo = 0;
GLuint program;

Vector3 camPos;
Vector3 camRot;

//methods
void initSDL_GL();
void cleanSDL_GL();
void manageShaders();
void compileShaders(GLuint* pshader, const char *data[], int nShaders);
void createScreenMesh();

//main methods
void glManager_Init() {
    initSDL_GL();
    createScreenMesh();
}

void glManager_Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    getCameraPosition(&camPos.x, &camPos.y, &camPos.z);
    GLint camPosGL = glGetUniformLocation(program, "camPos");
    glUniform3f(camPosGL, camPos.x, camPos.y, camPos.z);

    getCameraRotation(&camRot.x, &camRot.y, &camRot.z);
    GLuint camRotGL = glGetUniformLocation(program, "camRot");
    glUniform3f(camRotGL, camRot.x, camRot.y, camRot.z);

    Vector3 forward = getCameraForward();
    GLuint forwardGL = glGetUniformLocation(program, "forward");
    glUniform3f(forwardGL, forward.x, forward.y, forward.z);

    GLuint resolutionGL = glGetUniformLocation(program, "resolution");
    glUniform2f(resolutionGL, SCREEN_WIDTH, SCREEN_HEIGHT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    SDL_GL_SwapWindow(win);
}

void glManager_Clean()
{
    cleanSDL_GL();
}

//other methods
void cleanSDL_GL()
{
    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void initSDL_GL()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    SDL_GL_SetAttribute(GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    win = SDL_CreateWindow("Voxel Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    glctx = SDL_GL_CreateContext(win);
    glewInit();
}

void createScreenMesh()
{
    //setup
    float triangles[6 * 2] = {
       -1, -1, 1, -1, 1, 1,
       -1, -1, -1, 1, 1, 1
    };

    //setup vao and vbo
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), triangles, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //unbind vao and vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //render here
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    manageShaders();
}

void manageShaders()
{
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    const char *shaderSources[2];
    int error;

    shaderSources[0] = readFile("src/shaders/vertex.vert", &error);
    if (error) {
        printf("vs err=%d ptr=%p\n", error, (void*)shaderSources[0]);
    }

    shaderSources[1] = readFile("src/shaders/raymarching.frag", &error);
    if (error) {
        printf("fs err=%d ptr=%p\n", error, (void*)shaderSources[1]);
    }

    GLuint shaders[3] = { vs, fs };

    compileShaders(shaders, shaderSources, 2);
}

void compileShaders(GLuint* pshader, const char *data[], int nShaders)
{
    GLint succes;
    char infoLog[512];

    for (int i = 0; i < nShaders; i++)
    {
        glShaderSource(pshader[i], 1, &data[i], NULL);
        glCompileShader(pshader[i]);

        glGetShaderiv(pshader[i], GL_COMPILE_STATUS, &succes);
        if (!succes)
        {
            glGetShaderInfoLog(pshader[i], 512, NULL, infoLog);
            printf("Shader Compilation Failed:\n%s\n", infoLog);
        }
    }

    program = glCreateProgram();

    for (int i = 0; i < nShaders; i++)
    {
        glAttachShader(program, pshader[i]);
    }
    glLinkProgram(program);
}
