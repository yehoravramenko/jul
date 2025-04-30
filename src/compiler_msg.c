#include "compiler_msg.h"

#include <stdio.h>
#include <stdlib.h>

void compiler_error(const char *msg)
{
    //TODO: Make it colorful
    printf("ERROR: %s\n", msg);
    exit(-1);
}

void compiler_warning(const char *msg)
{
    //TODO: Make it colorful
    printf("WARNING: %s\n", msg);
}

void compiler_msg(const char *msg)
{
    printf("%s\n", msg);
}