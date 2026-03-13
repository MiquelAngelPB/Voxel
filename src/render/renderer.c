#include "GL/glew.h"
#include "gpu/gpuDebug.h"
#include "gpu/shader.h"
#include "gpu/texture.h"
#include "gpu/buffer.h"
#include "platform/settings.h"
#include "platform/window.h"
#include "game/camera.h"

GLuint programGraphic;
GLuint programCompute;
GLuint screenTexture;
meshBuffers screenMesh = {0};

void initRenderer()
{
    //Screen mesh
    float screenTriangles[6 * 2] = {
       -1, -1,  1, -1, 1, 1,
       -1, -1, -1,  1, 1, 1
    };
    createMesh(screenTriangles, 6, &screenMesh);

    //Screen texture
    screenTexture = createTexture(pSettings->screenWidth, pSettings->screenHeight);

    //Compute shader for raymarching into a texture
    shaderData computeShaders[1];
    computeShaders[0] = loadShader(SHADER_COMPUTE, "./src/render/shaders/raymarching.comp");
    compileShaders(computeShaders, 1, &programCompute);

    useProgram(programCompute);
    printGLError("when setting up compute shader");

    //Vertex and fragment shaders for rendering the texture
    shaderData graphicShaders[2];
    graphicShaders[0] = loadShader(SHADER_VERTEX, "./src/render/shaders/vertex.vert");
    graphicShaders[1] = loadShader(SHADER_FRAGMENT, "./src/render/shaders/fragment.frag");
    compileShaders(graphicShaders, 2, &programGraphic);

    int textureSlot = 0;
    useProgram(programGraphic);
    setUniform(UNIFORM_TEXTURE, "screenTexture", &textureSlot, &programGraphic);
    printGLError("when setting up graphics shaders");
}

void updateRenderer()
{
    //compute pass
    useProgram(programCompute);
    setUniform(UNIFORM_V3, "camPos", &pCamera->pos, &programCompute);
    setUniform(UNIFORM_V3, "forward", &pCamera->forward, &programCompute);
    bindImageTexture(screenTexture, 0);
    runComputeShader((pSettings->screenWidth + 15) / 16, (pSettings->screenHeight + 15) / 16, 1);

    //rendering pass
    useProgram(programGraphic);
    bindSampleTexture(screenTexture, 0);
    //useMesh(&screenMesh);
    drawMesh(&screenMesh, 6);
}

void cleanRenderer()
{
    cleanMesh(&screenMesh);
    cleanTexture(screenTexture);
}