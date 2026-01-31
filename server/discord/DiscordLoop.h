#pragma once

#include <condition_variable>
#include <mutex>

extern std::mutex g_discordMutex;
extern std::condition_variable g_discordCv;

void discordUpdateLoop();
