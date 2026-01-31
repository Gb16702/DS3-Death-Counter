#pragma once

#include <atomic>

struct Settings {
    static constexpr const char* FILENAME = "settings.json";

    std::atomic<bool> isDeathCountVisible = true;
    std::atomic<bool> isPlaytimeVisible = true;
    std::atomic<bool> isDiscordRpcEnabled = true;
    std::atomic<bool> isBorderlessFullscreenEnabled = false;
    std::atomic<bool> isAutoStartEnabled = false;

    void LoadSettings();
    void SaveSettings();
};

extern Settings g_settings;
