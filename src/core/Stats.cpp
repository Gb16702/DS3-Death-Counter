#include "Stats.h"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace Stats {
    std::string GetCurrentTimestamp() {
        std::time_t now = std::time(nullptr);
        std::tm tm{};
        localtime_s(&tm, &now);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    double CalculateDeathsPerHour(int deaths, int durationMs) {
        if (durationMs <= 0) {
            return 0.0;
        }

        double hours = durationMs / 3600000.0;
        return deaths / hours;
    }
}
