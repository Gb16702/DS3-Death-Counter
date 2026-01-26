#pragma once

#include "MemoryReader.h"

#include <expected>
#include <cstdint>

class DS3StatsReader {
private:
    MemoryReader reader;

    static constexpr uintptr_t GAMEDATAMAN_POINTER = 0x047572B8;
    static constexpr uintptr_t DEATH_COUNT_OFFSET = 0x98;
    static constexpr uintptr_t PLAYTIME_OFFSET = 0xA4;

    static constexpr wchar_t PROCESS_NAME[] = L"DarkSoulsIII.exe";

    std::expected<uint32_t, MemoryReaderError> ReadGameData(uintptr_t basePointer, uintptr_t offset);

public:
    std::expected<void, MemoryReaderError> Initialize();
    bool IsInitialized() const;
    std::expected<uint32_t, MemoryReaderError> GetDeathCount();
    std::expected<uint32_t, MemoryReaderError> GetPlayTime();
};
