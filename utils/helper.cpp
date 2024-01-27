#include "helper.h"

MODULEINFO GetModuleInfo(const char* szModule) {
    MODULEINFO modInfo = { 0 };
    wchar_t wszModule[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, szModule, -1, wszModule, MAX_PATH);
    HMODULE hModule = GetModuleHandle(wszModule);
    if (hModule != NULL) {
        GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));
    }
    return modInfo;
}

uintptr_t GetModBaseAddr() {
    uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);
    return modBase;
}

void NopBytesToggle(uintptr_t addr, const std::vector<unsigned char>& oriBytes, size_t size, bool restore) {
    DWORD oldProtect;
    if (restore) {
        VirtualProtect((LPVOID)addr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
        memset((LPVOID)addr, 0x90, size);
    }
    else {
        if (!oriBytes.empty()) {
            VirtualProtect((LPVOID)addr, oriBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
            memcpy((LPVOID)addr, oriBytes.data(), oriBytes.size());
        }
    }
    VirtualProtect((LPVOID)addr, size, oldProtect, &oldProtect);
}

void WriteToMemory(uintptr_t addressToWrite, char* valueToWrite, size_t byteNum) {
    DWORD oldProtection;
    VirtualProtect((LPVOID)(addressToWrite), byteNum, PAGE_EXECUTE_READWRITE, &oldProtection);
    memcpy((LPVOID)addressToWrite, valueToWrite, byteNum);
    VirtualProtect((LPVOID)(addressToWrite), byteNum, oldProtection, NULL);
}


uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets) {
    uintptr_t addr = ptr;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }
    return addr;
}

DWORD FindPattern(const char* pattern, const char* mask) {
    MODULEINFO mInfo = GetModuleInfo("sauerbraten.exe");
    uintptr_t base = GetModBaseAddr();
    DWORD size = mInfo.SizeOfImage;
    DWORD patternLength = static_cast<DWORD>(strlen(mask));
    for (DWORD i = 0; i < size - patternLength; i++) {
        bool found = true;
        for (DWORD j = 0; j < patternLength; j++) {
            if (mask[j] != '?' && pattern[j] != *reinterpret_cast<char*>(base + i + j)) {
                found = false;
                break;
            }
        }
        if (found) {
            return static_cast<DWORD>(i);
        }
    }
    return NULL;
}

FunctionAddrs FindAllPatterns() {
    FunctionAddrs functAddr;

    functAddr.HudPlayerAddr = FindPattern("\x83\x3D\xCC\xCC\xCC\xCC\xCC\x74\x08\x48\x8B\x05", "xx?????xxxxx");
    functAddr.GetClientAddr = FindPattern("\x48\x8B\x05\xCC\xCC\xCC\xCC\x3B\x88\xD8\x01\x00\x00\x74\x1D\x85", "xxx????xxxxxxxxx");
    functAddr.SpawnItems = FindPattern("\x48\x89\x6C\x24\x18\x48\x89\x74\x24\x20\x41\x54\x48\x63", "xxxxxxxxxxxxxx"); // not sure what to do here all sig gen attemps dont return a unknown byte
    functAddr.SwitchPlayerModel = FindPattern("\x8B\x0D\xCC\xCC\xCC\xCC\x48\x8B\x05\xCC\xCC\xCC\xCC\x48\x8D\x15\xCC\xCC\xCC\xCC\x89\x88\x88\x05\x00\x00\x44\x8B\x05\xCC\xCC\xCC\xCC\xB9\x66\x00\x00\x00\xE9", "xx????xxx????xxx????xxxxxxxxx????xxxxxx");
    functAddr.DoAttack = FindPattern("\x48\x83\xEC\x28\x80\x3D\xCC\xCC\xCC\xCC\xCC\x75\x16", "xxxxxx?????xx");
    functAddr.DoDamage = FindPattern("\x44\x88\x4C\x24\x20\x4C\x89\x44\x24\x18\x89\x4C", "xxxxxxxxxxxx"); // not sure what to do here all sig gen attemps dont return a unknown byte
    functAddr.Quit = FindPattern("\x40\x53\x48\x83\xEC\x20\xE8\xCC\xCC\xCC\xCC\xE8\xCC\xCC\xCC\xCC\x48", "xxxxxxx????x????x");

    return functAddr;
}
