#include <main_header.hpp>

int main(int argc, char** argv)
{
    std::string arg = argv[1];
    std::cout << "retreiving entry @" << arg << std::endl; 
    test_w_crow();
    return EXIT_SUCCESS;
}
