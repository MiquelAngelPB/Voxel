#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include "utilities.h"

//variables
SDL_Window* win = NULL;
SDL_GLContext glctx = NULL;
GLuint vao = 0;
GLuint vbo = 0;
GLuint program;

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

void glManager_Render(float camX, float camY, float camZ, float camRX, float camRY)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);

    GLint camPos = glGetUniformLocation(program, "camPos");
    glUniform3f(camPos, camX, camY, camZ);

    GLuint camRot = glGetUniformLocation(program, "camRot");
    camRX /= 800.0f;
    camRY /= 600.0f;
    glUniform2f(camRot, camRX, camRY);

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

    SDL_GL_SetAttribute(GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    win = SDL_CreateWindow("Voxel Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600, SDL_WINDOW_OPENGL);

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