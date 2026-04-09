#include "GL/glew.h"
#include "gpu/gpuDebug.h"
#include "gpu/shader.h"
#include "gpu/texture.h"
#include "gpu/buffer.h"
#include "platform/settings.h"
#include "platform/window.h"
#include "game/camera.h"

#include <math.h> //TODO: Remove this

GLuint programGraphic;
GLuint programCompute;
GLuint screenTexture;
GLuint tmpWorldBuffer;
meshBuffers screenMesh = {0};
int mapSize = 128; //TODO: Dont hardcode this

void initRenderer()
{
    //Buffer for testing DDA
    createBuffer(sizeof(int) * mapSize * mapSize * mapSize, 1, &tmpWorldBuffer);
    
    //TODO: Remove this, just for testing =========================
    int* tmpWorld = malloc(sizeof(int) * mapSize * mapSize * mapSize);
    for(int x = 0; x < mapSize; x++)
    {
        for(int z = 0; z < mapSize; z++)
        {
            int y = (int)floor(sin(z*100)*cos(x*100)*2 + 8);
            int cx = 70;
            int cy = rand() % 256;
            int cz = 0;
            tmpWorld[x + z * mapSize * mapSize + y * mapSize] = cx << 16 | cy << 8 | cz;
        }
    }
    tmpWorld[0] = 255 << 16 | 255 << 8 | 255;
    writeBuffer(sizeof(int) * mapSize * mapSize * mapSize, 1, &tmpWorldBuffer, tmpWorld);
    free(tmpWorld);
    // ============================================================

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
    float voxelSize = 1; //TODO: Dont hardcode this
    //setUniform(UNIFORM_FLOAT, "voxelSize", &voxelSize, &programCompute);
    setUniform(UNIFORM_V3, "mapStart", &(Vector3){0, 0, 0}, &programCompute); //TODO: Dont hardcode this
    setUniform(UNIFORM_V3, "mapEnd", &(Vector3){mapSize, mapSize, mapSize}, &programCompute); //TODO: Dont hardcode this
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
    cleanBuffer(sizeof(int) * mapSize * mapSize * mapSize, 0, &tmpWorldBuffer);
    cleanMesh(&screenMesh);
    cleanTexture(screenTexture);
}