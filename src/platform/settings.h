#ifndef settings_h
#define settings_h

#include <stdbool.h>

typedef struct{
    float sensitivity;
    int screenWidth;
    int screenHeight;
    bool debugMode;
} settingsData;

extern settingsData* pSettings;
void initSettings();

#endif