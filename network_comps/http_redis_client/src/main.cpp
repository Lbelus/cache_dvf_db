#include <main_header.hpp>

int main(int argc, char** argv)
{
    // std::string arg = argv[1];
    // std::cout << "retreiving entry @" << arg << std::endl;
    testMsgPacktoHiredis();
    // test_w_crow();
    test_w_crow_get_path();
    return EXIT_SUCCESS;
}
