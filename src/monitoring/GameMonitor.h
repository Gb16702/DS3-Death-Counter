#pragma once

#include <atomic>
#include <string>

extern std::string g_sessionStartTime;
extern int g_startingDeaths;
extern int g_lastKnownDeaths;
extern std::atomic<bool> g_sessionActive;
extern std::atomic<bool> g_running;

void gameMonitorLoop();
