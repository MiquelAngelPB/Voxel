//Implement this: https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html
//Also: https://www.youtube.com/watch?v=wg4om77Drr0
#include <SDL2/SDL.h>
//#include <GL/gl.h>
#include <GL/glew.h>
#include <stdio.h>
#include "utilities.h"

//variables
SDL_Window* win = NULL;
SDL_GLContext glctx = NULL;
GLuint vbo;
GLuint vao;
GLuint program;
GLuint screenTex;

//methods
void initSDL_GL();
void cleanSDL_GL();
void createScreenMesh();
void compileShaders(GLuint* pshader, const char *data[], int nShaders);
void manageSgaders();
GLuint createTexture(int w, int h);

//main()
int glManager_Init() {
    initSDL_GL();
    screenTex = createTexture(4, 4);

    createScreenMesh();
}

void glManager_Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
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

    win = SDL_CreateWindow("Voxel Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    800, 600, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    glctx = SDL_GL_CreateContext(win);

    glewInit();
}

void createScreenMesh()
{
    //setup
    float triangles[6 * 7] = {
       -1, -1,      0, 1, 1,    0, 0,
        1, -1,      1, 0, 1,    1, 0,
        1,  1,      1, 1, 0,    1, 1,

       -1, -1,      1, 1, 0,    0, 0,
       -1,  1,      1, 0, 1,    1, 1,
        1,  1,      0, 1, 1,    1, 0
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangles), &triangles, GL_STATIC_DRAW);

    //Position (2 floats)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);
    glEnableVertexAttribArray(0);

    //Color (3 floats)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Texture coords (2 floats)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //render
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    manageSgaders();
}

void manageSgaders()
{
    //vector shader
    const char* vShader = "#version 330 core\n"
    "layout(location = 0) in vec2 inPos;\n"
    "layout(location = 1) in vec3 inColor;\n"
    "layout(location = 2) in vec2 inTexCoord;\n"
    "out vec3 fragColor;\n"
    "out vec2 fragTexCoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(inPos, 0.0, 1.0);\n"
    "   fragColor = inColor;\n"
    "   fragTexCoord = inTexCoord;\n"
    "}\n";

    //fragment shader
    const char* fShader = "#version 330 core\n"
    "in vec3 fragColor;\n"
    "in vec2 fragTexCoord;\n"
    "out vec4 outColor;\n"
    "uniform sampler2D screenTexture;\n"
    "void main()\n"
    "{\n"
    "   outColor = texture(screenTexture, fragTexCoord);\n"
    "}\n";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint cs = glCreateShader(GL_COMPUTE_SHADER);

    const char *shaderSources[3];
    shaderSources[0] = (char*)vShader;
    shaderSources[1] = (char*)fShader;

    int csError;
    char* cpShader = readFile("./src/shaders/draw_screen.comp", &csError);
    if (csError == 0) //succes
    {
        shaderSources[2] = (char*)cpShader;
    }

    GLuint shaders[3] = { vs, fs, cs };

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

GLuint createTexture(int w, int h)
{
    unsigned char pixels[4 * 4 * 3] =
    {
        255,255,255,  0,0,0,      255,255,255,  0,0,0,
        0,0,0,        255,255,255,0,0,0,        255,255,255,
        255,255,255,  0,0,0,      255,255,255,  0,0,0,
        0,0,0,        255,255,255,0,0,0,        255,255,255
    };

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    return tex;
}