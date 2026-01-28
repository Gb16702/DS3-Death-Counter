#include "DiscordLoop.h"
#include "DiscordPresence.h"
#include "../core/Log.h"
#include "../core/Settings.h"
#include "../core/ZoneNames.h"
#include "../memory/DS3StatsReader.h"
#include "../monitoring/GameMonitor.h"

#include "discord_rpc.h"

#include <chrono>

std::mutex g_discordMutex;
std::condition_variable g_discordCv;

void discordUpdateLoop() {
    DS3StatsReader statsReader;
    bool gameConnected = false;
    uint32_t currentDeaths = 0;
    uint32_t currentPlaytime = 0;
    int minutesSinceSync = 5;

    g_discord.Initialize();

    while (g_running) {
        std::unique_lock<std::mutex> lock(g_discordMutex);

        if (!g_settings.isDiscordRpcEnabled) {
            Discord_ClearPresence();
            g_discordCv.wait_for(lock, std::chrono::seconds(15));
            continue;
        }

        if (!statsReader.IsInitialized()) {
            if (statsReader.Initialize()) {
                gameConnected = true;
                log(LogLevel::INFO, "Game detected, starting Discord presence");
                minutesSinceSync = 5;
            } else {
                if (gameConnected) {
                    log(LogLevel::WARN, "Game disconnected");
                    Discord_ClearPresence();
                    gameConnected = false;
                }
                Discord_RunCallbacks();
                g_discordCv.wait_for(lock, std::chrono::seconds(15));
                continue;
            }
        }

        if (minutesSinceSync >= 5) {
            auto deathsResult = statsReader.GetDeathCount();

            if (deathsResult) {
                currentDeaths = *deathsResult;
            }
            minutesSinceSync = 0;
        }

        auto playtimeResult = statsReader.GetPlayTime();
        if (playtimeResult) {
            currentPlaytime = *playtimeResult;
        }

        std::string zoneName = "Unknown Area";
        auto zoneResult = statsReader.GetPlayRegion();
        if (zoneResult) {
            zoneName = GetZoneName(*zoneResult);
        }

        g_discord.Update(currentDeaths, currentPlaytime, zoneName);

        minutesSinceSync++;

        Discord_RunCallbacks();
        g_discordCv.wait_for(lock, std::chrono::seconds(15));
    }
}
