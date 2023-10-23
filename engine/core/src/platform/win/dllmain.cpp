#include <Windows.h>

#include <iostream>
#include <memory>
#include <thread>

#include "frustrum/window.hpp"
#include "frustrum/platform/win/win_window.hpp"

HINSTANCE g_hInstance = nullptr;

namespace frs {

}

// Use for ref https://learn.microsoft.com/en-us/windows/win32/dlls/dllmain
// https://ikrima.dev/dev-notes/cpp/crt-init/
BOOL DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    if (hinstDLL == nullptr) {
        return FALSE;
    }

    // frs::Engine::Init(hinstDLL);
    g_hInstance = hinstDLL;

    std::cout << std::this_thread::get_id() << std::endl;

    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        std::cout << "Process attach!" << std::endl;

        if (lpReserved != nullptr) {
            std::cout << "DLL is being loaded statically as a dependency!" << std::endl;
        }

        break;

    case DLL_PROCESS_DETACH:
        std::cout << "Process detach!" << std::endl;

        if (lpReserved != nullptr) {
            std::cout << "Process is terminating!" << std::endl;
            // No cleanup required?
        }

        break;

    case DLL_THREAD_ATTACH:
        std::cout << "Thread attach!" << std::endl;
        break;

    case DLL_THREAD_DETACH:
        std::cout << "Thread detach!" << std::endl;
        break;
    default:
        // Some error message if you even can do it?
        return FALSE;
    }

    return TRUE;
}