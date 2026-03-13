#ifndef settings_h
#define settings_h

typedef struct{
    float sensitivity;
    int screenWidth;
    int screenHeight;
} settingsData;

extern settingsData* pSettings;
void initSettings();

#endif