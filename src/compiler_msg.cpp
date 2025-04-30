#include "compiler_msg.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace Compiler {
    void Error(const char *msg)
    {
        //TODO: Make it colorful
        printf("ERROR: %s\n", msg);
        exit(-1);
    }

    void Warning(const char *msg)
    {
        //TODO: Make it colorful
        printf("WARNING: %s\n", msg);
    }

    void Msg(const char *msg)
    {
        printf("%s\n", msg);
    }
}