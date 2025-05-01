#include "compiler_msg.hpp"

auto main(int argc, char **) -> int
{
    if (argc < 2) {
        compiler::error("No file specified."
                        "\n\nUsage: jul [target](.jul) <options>");
    }
    return 0;
}