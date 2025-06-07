#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

class DS3MemoryReader {
private:
    HANDLE processHandle;
    DWORD processId;
    uintptr_t moduleBase;

public:
    DS3MemoryReader() : processHandle(nullptr), processId(0), moduleBase(0) {}

    ~DS3MemoryReader() {
        if (processHandle) {
            CloseHandle(processHandle);
        }
    }

    bool Initialize() {
        if (!FindProcess(L"DarkSoulsIII.exe")) {
            std::cout << "Error: Game not found" << std::endl;
            return false;
        }

        processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);
        if (!processHandle) {
            std::cout << "Error: Cannot open process. Run as administrator" << std::endl;
            return false;
        }

        if (!GetModuleBase(L"DarkSoulsIII.exe")) {
            std::cout << "Error: Cannot find Game module" << std::endl;
            return false;
        }

        return true;
    }

    int GetDeathCount() {
        const uintptr_t GAMEDATAMAN_POINTER = 0x047572B8;
        const uintptr_t DEATH_COUNT_OFFSET = 0x98;

        uintptr_t pointerAddress = moduleBase + GAMEDATAMAN_POINTER;

        uintptr_t gameDataManAddress = 0;
        if (!ReadMemory(pointerAddress, gameDataManAddress)) {
            return -1;
        }

        uintptr_t deathCountAddress = gameDataManAddress + DEATH_COUNT_OFFSET;

        int deathCount = 0;
        if (!ReadMemory(deathCountAddress, deathCount)) {
            return -1;
        }

        return deathCount;
    }

private:
    bool FindProcess(const std::wstring& processName) {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE) return false;

        PROCESSENTRY32 processEntry = {};
        processEntry.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(snapshot, &processEntry)) {
            do {
                if (wcscmp(processName.c_str(), processEntry.szExeFile) == 0) {
                    processId = processEntry.th32ProcessID;
                    CloseHandle(snapshot);
                    return true;
                }
            } while (Process32Next(snapshot, &processEntry));
        }

        CloseHandle(snapshot);
        return false;
    }

    bool GetModuleBase(const std::wstring& moduleName) {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
        if (snapshot == INVALID_HANDLE_VALUE) return false;

        MODULEENTRY32 moduleEntry = {};
        moduleEntry.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(snapshot, &moduleEntry)) {
            do {
                if (wcscmp(moduleName.c_str(), moduleEntry.szModule) == 0) {
                    moduleBase = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
                    CloseHandle(snapshot);
                    return true;
                }
            } while (Module32Next(snapshot, &moduleEntry));
        }

        CloseHandle(snapshot);
        return false;
    }

    template<typename T>
    bool ReadMemory(uintptr_t address, T& value) {
        SIZE_T bytesRead;
        return ReadProcessMemory(processHandle, reinterpret_cast<LPCVOID>(address),
            &value, sizeof(T), &bytesRead) && bytesRead == sizeof(T);
    }
};

int main() {
    DS3MemoryReader reader;

    if (!reader.Initialize()) {
        return 1;
    }

    int deathCount = reader.GetDeathCount();

    if (deathCount >= 0) {
        std::cout << "Deaths: " << deathCount << std::endl;
    }
    else {
        std::cout << "Failed to read death count" << std::endl;
    }

    return 0;
}
