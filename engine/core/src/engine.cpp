#include "frustrum/engine.hpp"
#include "frustrum/window.hpp"

#include <iostream>

void test() {
    std::cout << "test" << std::endl;
    std::cout << FRS_EXPAND_STRINGIFY(FRS_PLATFORM_IMPL(window));
}
