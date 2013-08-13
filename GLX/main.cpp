#include "Exports.hpp"

extern "C" __declspec(dllexport) bool __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
            hInstance = hinstDLL;
        }
        break;

        case DLL_PROCESS_DETACH:
        {
            UnMapSharedMemory();
        }
        break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }
    return true;
}
