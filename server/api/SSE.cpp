#include "SSE.h"
#include "../core/Log.h"
#include "../core/Settings.h"

#include "json.hpp"

#include <chrono>
#include <thread>

using json = nlohmann::json;

static bool sendEvent(httplib::DataSink& sink, const std::string& type, const json& data) {
    json event = {
        {"type", type},
        {"data", data}
    };
    std::string message = "data: " + event.dump() + "\n\n";
    return sink.write(message.c_str(), message.size());
}

void streamStats(DS3StatsReader& statsReader, httplib::DataSink& sink) {
    uint32_t lastDeathCount = 0;
    uint32_t lastPlayTime = 0;
    bool wasConnected = false;
    bool firstRun = true;
    bool statusSent = false;
    int reconnectDelay = 1500;
    constexpr int maxReconnectDelay = 30000;

    log(LogLevel::INFO, "Client connected to SSE stream");

    while (true) {
        bool isConnected = statsReader.IsProcessRunning();

        if (!statsReader.IsInitialized()) {
            auto initResult = statsReader.Initialize();
            if (initResult) {
                isConnected = true;
            }
        }

        if (isConnected != wasConnected || !statusSent) {
            json statusData = {{"status", isConnected ? "in_game" : "not_running"}};
            if (!sendEvent(sink, "status", statusData)) {
                log(LogLevel::INFO, "Client disconnected from SSE stream");
                return;
            }
            statusSent = true;

            if (isConnected && !wasConnected) {
                log(LogLevel::INFO, "Connected to DarkSoulsIII.exe");
                reconnectDelay = 1500;
            } else if (!isConnected && wasConnected) {
                log(LogLevel::WARN, "Game disconnected, waiting...");
                reconnectDelay = 1500;
            }
            wasConnected = isConnected;
        }

        if (!isConnected) {
            std::this_thread::sleep_for(std::chrono::milliseconds(reconnectDelay));
            reconnectDelay = std::min(reconnectDelay * 2, maxReconnectDelay);
            continue;
        }

        auto deathsResult = statsReader.GetDeathCount();
        auto playTimeResult = statsReader.GetPlayTime();

        json statsData;
        bool changed = false;

        if (g_settings.isDeathCountVisible && deathsResult && (firstRun || *deathsResult != lastDeathCount)) {
            lastDeathCount = *deathsResult;
            statsData["deaths"] = lastDeathCount;
            changed = true;
        }

        if (g_settings.isPlaytimeVisible && playTimeResult && (firstRun || *playTimeResult != lastPlayTime)) {
            lastPlayTime = *playTimeResult;
            statsData["playtime"] = lastPlayTime;
            changed = true;
        }

        if (changed) {
            if (!sendEvent(sink, "stats", statsData)) {
                log(LogLevel::INFO, "Client disconnected from SSE stream");
                return;
            }
            firstRun = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }
}
