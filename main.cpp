#include <Windows.h>
#include <vector>

using namespace std;

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

DWORD WINAPI MainThread(HMODULE hModule)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    printf("Dll loaded.");

    Sleep(2000);

    DWORD moduleBase = (DWORD)GetModuleHandle("ac_client.exe");

    while (!GetAsyncKeyState(VK_END))
    {
        int* gun_ammo = (int*)GetPointerAddress(moduleBase + 0x0017E0A8, {0x140});
        int* pistol_ammo = (int*)GetPointerAddress(moduleBase + 0x0017E0A8, { 0x12C });
        int* gun_round = (int*)GetPointerAddress(moduleBase + 0x0017E0A8, { 0x11C });
        int* pistol_round = (int*)GetPointerAddress(moduleBase + 0x0017E0A8, { 0x108 });
        int* grenade = (int*)GetPointerAddress(moduleBase + 0x0017E0A8, { 0x144 });
        int* health = (int*)GetPointerAddress(moduleBase + 0x0017E0A8, { 0xEC });
        int* armor = (int*)GetPointerAddress(moduleBase + 0x0017E0A8, { 0xF0 });

        *gun_ammo = 100;
        *pistol_ammo = 100;
        *gun_round = 60;
        *pistol_round = 60;
        *grenade = 10;
        *health = 100;
        *armor = 100;
    }

    if (GetAsyncKeyState(VK_END))
    {
        fclose(f);
        FreeConsole();
    }

    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        if (lpvReserved != nullptr)
        {
            break;
        }
        break;
    }
    return TRUE;
}
