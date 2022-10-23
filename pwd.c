#include "pwd.h"

void pwd()
{
    if (getcwd(cwd, sizeof(cwd)))
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("Error");
    }
}