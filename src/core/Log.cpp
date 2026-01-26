#include "Log.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <syncstream>

void log(LogLevel level, const std::string& message) {
    std::time_t now = std::time(nullptr);
    std::tm tm{};
    localtime_s(&tm, &now);

    const char* levelStr = "INFO ";
    switch (level) {
        case LogLevel::INFO:
            levelStr = "INFO ";
            break;

        case LogLevel::WARN:
            levelStr = "WARN ";
            break;

        case LogLevel::ERR:
            levelStr = "ERROR ";
            break;
    }

    std::osyncstream(std::cout) << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S] ") << levelStr << message << std::endl;
}
