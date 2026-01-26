#pragma once

#include "httplib.h"
#include "../memory/DS3StatsReader.h"

#include <chrono>

constexpr const char* APP_VERSION = "1.0.0";
constexpr const char* ALLOWED_ORIGIN = "http://localhost:5173";
constexpr int SERVER_PORT = 3000;

void setupRoutes(httplib::Server& server, DS3StatsReader& statsReader, std::chrono::steady_clock::time_point startTime);
