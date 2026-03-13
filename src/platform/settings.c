#include "platform/settings.h"

settingsData settings;
settingsData* pSettings;
void initSettings()
{
    settings = (settingsData) {
        .sensitivity = 0.00078539816 * 2,
        .screenWidth = 800,
        .screenHeight = 600
    };

    pSettings = &settings;
}

//TODO: Parse config file