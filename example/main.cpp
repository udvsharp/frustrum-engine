#include "frustrum/engine.hpp"
#include "frustrum/window.hpp"

#include <Windows.h>

#include <iostream>
#include <thread>

int main(int argc, char** argv)
{
    using namespace std::chrono_literals;

    test();

    std::cout << std::this_thread::get_id() << std::endl;

    auto window = frs::window {};
    window.init();
    window.show();

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
