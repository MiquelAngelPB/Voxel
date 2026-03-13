#include "platform/settings.h"

settingsData settings;
settingsData* pSettings;
void initSettings()
{
    settings = (settingsData) {
        .sensitivity = 0.00078539816 * 2,
        .screenWidth = 560,
        .screenHeight = 315,
        .debugMode = true
    };

    pSettings = &settings;
}

//TODO: Parse config file