#include "player.hpp"
#include "inventory.hpp"
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

std::atomic<bool> g_Running{ true };
HINSTANCE g_DllInstance{ nullptr };
HANDLE g_MainThread{ INVALID_HANDLE_VALUE };
DWORD g_MainThreadId = -1;

DWORD GetPointerAddress(DWORD ptr, vector<DWORD> offsets)
{
    DWORD address = ptr;
    for (int i{ 0 }; i < offsets.size(); i++)
    {
        address = *(DWORD*)address;
        address += offsets[i];
    }
    return address;
}

DWORD Main(void*)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    printf("Dll loaded.\n");
    Sleep(2000);

    uintptr_t exeBaseAddress = (uintptr_t)GetModuleHandle(nullptr);

    Player* g_localPlayer = *(Player**)(exeBaseAddress + 0x0017E0A8);
    Inventory* g_inventory = *(Inventory**)(exeBaseAddress + 0x0017E0A8);

    while (true)
    {
        if (GetAsyncKeyState(VK_END))
        {
            break;
        }

        g_inventory->health = 1000;
        g_inventory->armor = 1000;
        g_inventory->gun_ammo = 100;
        g_inventory->gun_round = 60;
        g_inventory->pistol_ammo = 100;
        g_inventory->pistol_round = 60;
        g_inventory->dpistol_ammo = 100;
        g_inventory->dpistol_round = 60;
        g_inventory->grenade = 10;      
    }

    FreeConsole();
    CloseHandle(g_MainThread);
    FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);
    return EXIT_SUCCESS;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,
    DWORD fdwReason,
    void*
)
{
    DisableThreadLibraryCalls(hinstDLL);

    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        g_DllInstance = hinstDLL;
        g_MainThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, nullptr, 0, &g_MainThreadId);
    }
    return TRUE;
}
