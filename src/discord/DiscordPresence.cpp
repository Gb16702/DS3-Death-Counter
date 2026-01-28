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

void DiscordPresence::Update(uint32_t deaths, uint32_t playtimeMs, const std::string& zoneName) {
    if (!initialized) {
        return;
    }

    if (deaths == 0) {
        detailsBuffer = "No deaths yet";
    } else {
        detailsBuffer = "Died " + std::to_string(deaths) + (deaths == 1 ? " time" : " times");
    }

    stateBuffer = zoneName;

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
