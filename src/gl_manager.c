#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include "utilities.h"
#include "camera.h"
#include "vector.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

//variables
SDL_Window* win = NULL;
SDL_GLContext glctx = NULL;
GLuint vao = 0;
GLuint vbo = 0;
GLuint programGraphic;
GLuint programCompute;
GLuint screenTexture;

Vector3 camPos;
Vector3 camRot;

//methods
void initSDL_GL();
void cleanSDL_GL();
void setStaticUniforms();
void setDynamicUniforms();
void manageShaders();
void compileShaders(GLuint* pshader, const char *data[], int nShaders, GLuint *pProgram);
void createScreenMesh();
void createScreenTexture();
void printGLError(char* context);

//main methods
void glManager_Init() {
    initSDL_GL();
    createScreenMesh();
    createScreenTexture();
    setStaticUniforms();
}

void glManager_Render()
{
    glUseProgram(programCompute);
    setDynamicUniforms();
    glBindImageTexture(0, screenTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
    glDispatchCompute((SCREEN_WIDTH + 15) / 16, (SCREEN_HEIGHT + 15) / 16, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    glUseProgram(programGraphic);
    glClear(GL_COLOR_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, screenTexture);

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
    glDeleteTextures(1, &screenTexture);

    //unbind vao and vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    printGLError("cleaning OpenGL");

    SDL_GL_DeleteContext(glctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void initSDL_GL()
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
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    printGLError("initializing OpenGL");
    glctx = SDL_GL_CreateContext(win);
    glewInit();
}

void setStaticUniforms()
{
    //once per program
    GLuint screenTexGL = glGetUniformLocation(programCompute, "screenTexture");
    glUniform1i(screenTexGL, 0);
}

void setDynamicUniforms()
{
    //once per frame
    getCameraPosition(&camPos.x, &camPos.y, &camPos.z);
    GLuint camPosGL = glGetUniformLocation(programCompute, "camPos");
    glUniform3f(camPosGL, camPos.x, camPos.y, camPos.z);

    Vector3 forward = getCameraForward();
    GLuint forwardGL = glGetUniformLocation(programCompute, "forward");
    glUniform3f(forwardGL, forward.x, forward.y, forward.z);
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

    printGLError("creating screen mesh");
    manageShaders();
}

void createScreenTexture()
{
    float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };

    glCreateTextures(GL_TEXTURE_2D, 1, &screenTexture);

    glTextureParameteri(screenTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(screenTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(screenTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTextureParameteri(screenTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTextureParameterfv(screenTexture, GL_TEXTURE_BORDER_COLOR, borderColor);  

    glTextureStorage2D(screenTexture, 1, GL_RGBA8, SCREEN_WIDTH, SCREEN_HEIGHT);
    printGLError("creating screen texture");
}

void manageShaders()
{
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    const char *graphicShaderSrc[2];
    const char *computeShaderSrc[1];
    int error;

    graphicShaderSrc[0] = readFile("src/shaders/vertex.vert", &error);
    graphicShaderSrc[1] = readFile("src/shaders/fragment.frag", &error);

    computeShaderSrc[0] = readFile("src/shaders/raymarching comp", &error);

    GLuint graphicShaders[2] = { vs, fs };
    GLuint computeShaders[1] = { cs };

    printGLError("creating shaders");
    compileShaders(graphicShaders, graphicShaderSrc, 2, &programGraphic);
    compileShaders(computeShaders, computeShaderSrc, 1, &programCompute);
}

void compileShaders(GLuint* pshader, const char *data[], int nShaders, GLuint *pProgram)
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

    *pProgram = glCreateProgram();

    for (int i = 0; i < nShaders; i++)
    {
        glAttachShader(*pProgram, pshader[i]);
    }
    glLinkProgram(*pProgram);
    
    glGetProgramiv(*pProgram, GL_LINK_STATUS, &succes);
    if (!succes)
    {
        glGetProgramInfoLog(*pProgram, 512, NULL, infoLog);
        printf("Linking Failed:\n%s\n", infoLog);
    }
}

void printGLError(char* context)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        printf("OpenGL error when %s: %d\n", context, error);
    }
}