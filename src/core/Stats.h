#pragma once

#include <string>

namespace Stats {
    std::string GetCurrentTimestamp();
    double CalculateDeathsPerHour(int deaths, int durationMs);
}
