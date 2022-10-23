#include "echo.h"

void echo(char **args)
{
    for (int i = 1; args[i]!=NULL ; i++)
        printf("%s ", args[i]);
    printf("\n");
}