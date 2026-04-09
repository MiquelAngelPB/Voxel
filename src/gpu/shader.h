#ifndef shader_h
#define shader_h

typedef enum {
    SHADER_VERTEX,
    SHADER_FRAGMENT,
    SHADER_COMPUTE
} shaderType;

typedef enum {
    UNIFORM_V3,
    UNIFORM_TEXTURE,
    UNIFORM_FLOAT
} uniformType;

typedef struct {
    GLuint pShader;
    const char* content;
    shaderType type;
} shaderData;

shaderData loadShader(shaderType type, char* path);
void compileShaders(shaderData* shaders, int nShaders, GLuint* pProgram);
void setUniform(uniformType type, char* name, void* data, GLuint* pProgram);
void useProgram(GLuint program);
void runComputeShader(int x, int y, int z);

#endif