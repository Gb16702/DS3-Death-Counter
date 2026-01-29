#include "DiscordPresence.h"
#include "../core/Log.h"

#include "discord_rpc.h"

#include <ctime>
#include <sstream>

constexpr const char* DISCORD_APP_ID = "1464534094405832923";

DiscordPresence g_discord;

DiscordPresence::~DiscordPresence() {
    Shutdown();
}

void DiscordPresence::Initialize() {
    DiscordEventHandlers handlers{};

    handlers.ready = [](const DiscordUser* user) {
        log(LogLevel::INFO, "Discord connected as " + std::string(user->username));
    };

    handlers.disconnected = [](int errorCode, const char* message) {
        log(LogLevel::WARN, "Discord disconnected: " + std::string(message));
    };

    handlers.errored = [](int errorCode, const char* message) {
        log(LogLevel::ERR, "Discord error: " + std::string(message));
    };

    Discord_Initialize(DISCORD_APP_ID, &handlers, 1, nullptr);
    Discord_RunCallbacks();

    startTimestamp = time(nullptr);
    initialized = true;

    log(LogLevel::INFO, "Discord remote procedure call initialized");
}

void DiscordPresence::Update(uint32_t deaths, uint32_t playtimeMs, const std::string& zoneName, bool inBossFight, bool inMainMenu, bool isBossZone) {
    if (!initialized) {
        return;
    }

    if (inMainMenu) {
        detailsBuffer = "In Main Menu";
        stateBuffer = "";
    } else {
        if (inBossFight) {
            detailsBuffer = "Fighting " + zoneName;
        } else if (zoneName == "Firelink Shrine" || zoneName == "Dark Firelink Shrine") {
            detailsBuffer = "Resting at " + zoneName;
        } else if (isBossZone) {
            detailsBuffer = "Exploring " + zoneName + " Arena";
        } else {
            detailsBuffer = "Exploring " + zoneName;
        }

        uint32_t totalMinutes = playtimeMs / 60000;
        uint32_t hours = totalMinutes / 60;
        uint32_t minutes = totalMinutes % 60;

        std::string playtimeStr;
        if (hours > 0) {
            playtimeStr = std::to_string(hours) + "H " + std::to_string(minutes) + "M";
        } else {
            playtimeStr = std::to_string(minutes) + "M";
        }

        if (deaths == 0) {
            stateBuffer = "No deaths yet. Current run: " + playtimeStr;
        } else {
            stateBuffer = "Died " + std::to_string(deaths) + (deaths == 1 ? " time. " : " times. ") + "Current run: " + playtimeStr;
        }
    }

    DiscordRichPresence presence{};
    presence.details = detailsBuffer.c_str();
    presence.state = stateBuffer.c_str();
    presence.largeImageKey = "ds3_logo";
    presence.startTimestamp = startTimestamp;

    Discord_UpdatePresence(&presence);
}

void DiscordPresence::Shutdown() {
    if (initialized) {
        Discord_Shutdown();
        initialized = false;
        log(LogLevel::INFO, "Discord remote procedure call shutdown");
    }
}

void DiscordPresence::ResetTimestamp() {
    startTimestamp = time(nullptr);
}
