#include "SessionDatabase.h"
#include "../core/Log.h"
#include "../core/Stats.h"

SessionDatabase g_sessionDb;

bool SessionDatabase::CreateTables() {
    const char* sessionsSql = R"(
        CREATE TABLE IF NOT EXISTS sessions (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            start_time TEXT,
            end_time TEXT,
            duration_ms INTEGER,
            starting_deaths INTEGER,
            ending_deaths INTEGER,
            session_deaths INTEGER,
            deaths_per_hour REAL
        )
    )";

    const char* playerStatsSql = R"(
        CREATE TABLE IF NOT EXISTS player_stats (
            id INTEGER PRIMARY KEY,
            total_deaths INTEGER,
            total_playtime_ms INTEGER,
            last_updated TEXT
        )
    )";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, sessionsSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        log(LogLevel::ERR, "Failed to create sessions table: " + std::string(errMsg));
        sqlite3_free(errMsg);
        return false;
    }

    if (sqlite3_exec(db, playerStatsSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        log(LogLevel::ERR, "Failed to create player_stats table: " + std::string(errMsg));
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool SessionDatabase::Open() {
    int result = sqlite3_open(DB_FILE, &db);
    if (result != SQLITE_OK) {
        log(LogLevel::ERR, "Failed to open database: " + std::string(sqlite3_errmsg(db)));
        return false;
    }

    if (!CreateTables()) {
        return false;
    }

    log(LogLevel::INFO, "Database opened");
    return true;
}

bool SessionDatabase::SaveSession(const std::string& startTime, const std::string& endTime, int durationMs, int startingDeaths, int endingDeaths) {
    int sessionDeaths = endingDeaths - startingDeaths;
    double deathsPerHour = Stats::CalculateDeathsPerHour(sessionDeaths, durationMs);

    const char* sql = R"(
        INSERT INTO sessions(start_time, end_time, duration_ms, starting_deaths, ending_deaths, session_deaths, deaths_per_hour)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        log(LogLevel::ERR, "Failed to prepare statement");
        return false;
    }

    sqlite3_bind_text(stmt, 1, startTime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, endTime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, durationMs);
    sqlite3_bind_int(stmt, 4, startingDeaths);
    sqlite3_bind_int(stmt, 5, endingDeaths);
    sqlite3_bind_int(stmt, 6, sessionDeaths);
    sqlite3_bind_double(stmt, 7, deathsPerHour);

    int result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (result != SQLITE_DONE) {
        log(LogLevel::ERR, "Failed to save session");
        return false;
    }

    log(LogLevel::INFO, "Session saved: " + std::to_string(sessionDeaths) + " deaths");
    return true;
}

void SessionDatabase::Close() {
    if (db) {
        sqlite3_close_v2(db);
        db = nullptr;
        log(LogLevel::INFO, "Session database closed");
    }
}

SessionDatabase::~SessionDatabase() {
    Close();
}
