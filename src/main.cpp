#include "compiler_msg.hpp"

int main(int argc, char **)
{
    Compiler::Msg("jul");
    if (argc < 2) {
        Compiler::Error("No file specified."
                        "\n\nUsage: jul [target](.jul) <options>");
    }
    return 0;
}