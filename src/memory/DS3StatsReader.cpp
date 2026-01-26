#include "DS3StatsReader.h"

std::expected<uint32_t, MemoryReaderError> DS3StatsReader::ReadGameData(uintptr_t basePointer, uintptr_t offset) {
    uintptr_t pointerAddress = reader.GetModuleBase() + basePointer;

    uintptr_t baseAddress = 0;
    if (!reader.ReadMemory(pointerAddress, baseAddress)) {
        return std::unexpected(MemoryReaderError::ReadFailed);
    }

    if (baseAddress == 0) {
        return std::unexpected(MemoryReaderError::ReadFailed);
    }

    uintptr_t dataAddress = baseAddress + offset;

    uint32_t value = 0;
    if (!reader.ReadMemory(dataAddress, value)) {
        return std::unexpected(MemoryReaderError::ReadFailed);
    }

    return value;
}

std::expected<void, MemoryReaderError> DS3StatsReader::Initialize() {
    return reader.Initialize(PROCESS_NAME);
}

bool DS3StatsReader::IsInitialized() const {
    return reader.IsInitialized();
}

std::expected<uint32_t, MemoryReaderError> DS3StatsReader::GetDeathCount() {
    return ReadGameData(GAMEDATAMAN_POINTER, DEATH_COUNT_OFFSET);
}

std::expected<uint32_t, MemoryReaderError> DS3StatsReader::GetPlayTime() {
    return ReadGameData(GAMEDATAMAN_POINTER, PLAYTIME_OFFSET);
}
