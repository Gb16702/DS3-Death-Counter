#include "SSE.h"
#include "../core/Log.h"
#include "../core/Settings.h"

#include "json.hpp"

#include <chrono>
#include <thread>

using json = nlohmann::json;

void streamStats(DS3StatsReader& statsReader, httplib::DataSink& sink) {
    uint32_t lastDeathCount = 0;
    uint32_t lastPlayTime = 0;
    bool wasConnected = false;
    bool firstRun = true;
    int reconnectDelay = 1500;
    constexpr int maxReconnectDelay = 30000;

    log(LogLevel::INFO, "Client connected to SSE stream");

    while (true) {
        if (!statsReader.IsInitialized()) {
            auto initResult = statsReader.Initialize();
            if (!initResult) {
                if (wasConnected) {
                    log(LogLevel::WARN, "Game disconnected, waiting...");
                    wasConnected = false;
                    reconnectDelay = 1500;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(reconnectDelay));
                reconnectDelay = std::min(reconnectDelay * 2, maxReconnectDelay);
                continue;
            }
        }

        if (!wasConnected) {
            log(LogLevel::INFO, "Connected to DarkSoulsIII.exe");
            wasConnected = true;
            reconnectDelay = 1500;
        }

        if (!statsReader.IsProcessRunning()) {
            if (wasConnected) {
                log(LogLevel::WARN, "Game closed, waiting for reconnection...");
                wasConnected = false;
                reconnectDelay = 1500;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(reconnectDelay));
            reconnectDelay = std::min(reconnectDelay * 2, maxReconnectDelay);
            statsReader.Initialize();
            continue;
        }

        auto deathsResult = statsReader.GetDeathCount();
        auto playTimeResult = statsReader.GetPlayTime();

        json data;
        bool changed = false;

        if (g_settings.isDeathCountVisible && deathsResult && (firstRun || *deathsResult != lastDeathCount)) {
            lastDeathCount = *deathsResult;
            data["deaths"] = lastDeathCount;
            changed = true;
        }

        if (g_settings.isPlaytimeVisible && playTimeResult && (firstRun || *playTimeResult != lastPlayTime)) {
            lastPlayTime = *playTimeResult;
            data["playtime"] = lastPlayTime;
            changed = true;
        }

        if (changed) {
            std::string event = "data: " + data.dump() + "\n\n";
            if (!sink.write(event.c_str(), event.size())) {
                log(LogLevel::INFO, "Client disconnected from SSE stream");
                return;
            }
            firstRun = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
}
