#include "Settings.h"
#include "Log.h"

#include "json.hpp"

#include <fstream>

using json = nlohmann::json;

Settings g_settings;

void Settings::LoadSettings() {
    std::ifstream settingsFile(FILENAME);
    if (!settingsFile) {
        log(LogLevel::INFO, "No settings file, creating defaults");
        SaveSettings();
        return;
    }

    try {
        json settingsData;
        settingsFile >> settingsData;

        isDeathCountVisible = settingsData.value("isDeathCountVisible", true);
        isPlaytimeVisible = settingsData.value("isPlaytimeVisible", true);
        isDiscordRpcEnabled = settingsData.value("isDiscordRpcEnabled", true);
        isBorderlessFullscreenEnabled = settingsData.value("isBorderlessFullscreenEnabled", false);
        isAutoStartEnabled = settingsData.value("isAutoStartEnabled", false);
    }
    catch (...) {
        log(LogLevel::WARN, "Invalid settings.json, restoring defaults");
        SaveSettings();
    }
}

void Settings::SaveSettings() {
    json settingsData = {
        {"isDeathCountVisible", isDeathCountVisible.load()},
        {"isPlaytimeVisible", isPlaytimeVisible.load()},
        {"isDiscordRpcEnabled", isDiscordRpcEnabled.load()},
        {"isBorderlessFullscreenEnabled", isBorderlessFullscreenEnabled.load()},
        {"isAutoStartEnabled", isAutoStartEnabled.load()},
    };

    std::ofstream settingsFile(FILENAME);
    if (!settingsFile) {
        log(LogLevel::ERR, "Failed to save settings");
        return;
    }

    settingsFile << settingsData.dump(4);
}
