#include "compiler_msg.h"

int main(int argc, char **argv)
{
    compiler_msg("jul");
    if (argc < 2) {
        compiler_error("No file specified."
                    "\n\nUsage: jul [target](.jul) <options>");
    }
    return 0;
}