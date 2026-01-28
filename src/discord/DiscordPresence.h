#pragma once

#include <atomic>
#include <cstdint>
#include <string>

class DiscordPresence {
private:
    std::atomic<bool> initialized = false;
    int64_t startTimestamp = 0;
    std::string detailsBuffer;
    std::string stateBuffer;

public:
    DiscordPresence() = default;
    DiscordPresence(const DiscordPresence&) = delete;
    DiscordPresence& operator=(const DiscordPresence&) = delete;

    ~DiscordPresence();

    void Initialize();
    void Update(uint32_t deaths, uint32_t playtimeMs, const std::string& zoneName);
    void Shutdown();
};

extern DiscordPresence g_discord;
