#include <stdio.h>
#include <GL/glew.h>
#include "platform/settings.h"

void printGLError(char* context)
{
    if (pSettings->debugMode)
    {
        GLenum error = glGetError();
        while (error != GL_NO_ERROR)
        {
            printf("OpenGL error when %s: %d\n", context, error);
        }
    }
}

void glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    printf("---------------\n");
    printf("Debug message (%d): %s\n", id, message);

    char* sourceStr;
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             sourceStr = "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sourceStr = "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: sourceStr = "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     sourceStr = "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     sourceStr = "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           sourceStr = "Source: Other"; break;
    }
    printf("%s\n", sourceStr);

    char* typeStr;
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               typeStr = "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: typeStr = "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  typeStr = "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         typeStr = "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         typeStr = "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              typeStr = "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          typeStr = "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           typeStr = "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               typeStr = "Type: Other"; break;
    }
    printf("%s\n", typeStr);
    
    char* severityStr;
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         severityStr = "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severityStr = "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severityStr = "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severityStr = "Severity: notification"; break;
    }
    printf("%s\n", severityStr);
}

void enableGLDebug()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); 
    glDebugMessageCallback(glDebugOutput, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
}