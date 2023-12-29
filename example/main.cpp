#include "frustrum/window.hpp"
#include "frustrum/application.hpp"

#include <Windows.h>

#include <iostream>
#include <thread>

int main(int argc, char** argv)
{
    using namespace std::chrono_literals;

    std::cout << std::this_thread::get_id() << std::endl;

    auto app = frs::current_application();
    auto window = app->make_window();

    if (!app->init_window(frs::window_data::make_default(), window)) {
        return -1;
    }

    window->show(); 

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
