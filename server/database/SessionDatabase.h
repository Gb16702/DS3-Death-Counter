#pragma once

#include "sqlite3.h"

#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <vector>

struct Session {
    int id;
    std::string startTime;
    std::string endTime;
    int durationMs;
    int startingDeaths;
    int endingDeaths;
    int sessionDeaths;
    double deathsPerHour;
    int characterId;
};

struct PlayerStats {
    int totalDeaths;
    int totalPlaytimeMs;
    std::string lastUpdated;
};

struct Death {
    int id;
    uint32_t zoneId;
    std::string zoneName;
    int characterId;
    std::string timestamp;
    bool isBossDeath;
};

struct Character {
    int id;
    std::string name;
    int classId;
    std::string createdAt;
};

struct CharacterStatsRecord {
	int characterId;
	int level;
	int vigor;
	int attunement;
	int endurance;
	int vitality;
	int strength;
	int dexterity;
	int intelligence;
	int faith;
	int luck;
    std::string updatedAt;
};

struct DeathStats {
    int total;
    int bossDeaths;
    int nonBossDeaths;
};

class SessionDatabase {
private:
    sqlite3* db = nullptr;
    static constexpr const char* DB_FILE = "sessions.db";

    bool CreateTables();

public:
    SessionDatabase() = default;

    SessionDatabase(const SessionDatabase&) = delete;
    SessionDatabase& operator=(const SessionDatabase&) = delete;

    ~SessionDatabase();

    bool Open();
    bool SaveSession(const std::string& startTime, const std::string& endTime, int durationMs, int startingDeaths, int endingDeaths, int characterId);
    bool UpdatePlayerStats(int totalDeaths, int totalPlaytimeMs);
    std::optional<PlayerStats> GetPlayerStats();
    std::vector<Session> GetAllSessions();
    bool SaveDeath(uint32_t zoneId, const std::string& zoneName, int characterId, bool isBossDeath);
    std::vector<Death> GetAllDeaths(std::optional<int> characterId = std::nullopt);
    DeathStats GetDeathStats(std::optional<int> characterId = std::nullopt);
    std::map<std::string, int> GetDeathsByZone(std::optional<int> characterId = std::nullopt);
    std::map<std::string, int> GetDeathsByBoss(std::optional<int> characterId = std::nullopt);
    void Close();

    int GetOrCreateCharacter(const std::string& name, int classId);
    std::optional<Character> GetCharacter(int id);
    std::vector<Character> GetAllCharacters();

	bool SaveCharacterStats(int characterId, const CharacterStatsRecord& statsRecord);
	std::optional<CharacterStatsRecord> GetCharacterStats(int characterId);
};

extern SessionDatabase g_sessionDb;
