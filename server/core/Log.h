#pragma once

#include <string>

enum class LogLevel {
    INFO,
    WARN,
    ERR
};

void log(LogLevel level, const std::string& message);
