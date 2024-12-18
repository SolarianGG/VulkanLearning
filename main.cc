#include "first_app.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main(int argc, char const *argv[])
{
    lve::FirstApp app;

    try {
        app.Run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
