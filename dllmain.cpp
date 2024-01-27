#include <Windows.h>
#include "include/imgui_hook.h"
#include "include/imgui/imgui.h"
#include "main/main.h"

void MainThread(HMODULE hModule) {
    ImGuiHook::Load(RenderMenu);
    while (!GetAsyncKeyState(VK_NUMPAD0) & 1) {
        MainHack();
        Sleep(1);
    }
    QuitGame();
    FreeLibraryAndExitThread(hModule, 1);
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}