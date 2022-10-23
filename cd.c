#include "cd.h"

void cd(char **args)
{
    char path[1000];

    if (args[1] == NULL)
    {
        getcwd(currDirectory, sizeof(currDirectory));
        chdir(homeDirectory);
        strcpy(prevDirectory, currDirectory);
    }
    else if (args[2])
        printf("error: Invalid path/directory\n");
    else if (strcmp(args[1], "~") == 0)
    {
        getcwd(currDirectory, sizeof(currDirectory));
        chdir(homeDirectory);
        strcpy(prevDirectory, currDirectory);
    }
    else if (strcmp(args[1], ".") == 0)
    {
        getcwd(currDirectory, sizeof(currDirectory));
        strcpy(prevDirectory, currDirectory);

        return;
    }
    else if (args[1][0] == '~')
    {
        getcwd(currDirectory, sizeof(currDirectory));
        strcpy(path, homeDirectory);
        strcat(path, args[1] + 1);

        if (chdir(path) < 0)
        {
            perror("error: Invalid path/directory\n");
            return;
        }
        strcpy(prevDirectory, currDirectory);
    }
    else if (strcmp(args[1], "..") == 0)
    {
        getcwd(currDirectory, sizeof(currDirectory));
        chdir(args[1]);
        strcpy(prevDirectory, currDirectory);
    }
    else if (args[1][0] == '-')
    {
        if (prevDirectory[0] == '\0')
        {
            printf("error: No previous directory exists\n");
            return;
        }
        getcwd(currDirectory, sizeof(currDirectory));
        printf("%s\n", prevDirectory);
        if (chdir(prevDirectory) < 0)
            perror("Error");
        strcpy(prevDirectory, currDirectory);
    }
    else if (args[1][0] == '/')
    {
        getcwd(currDirectory, sizeof(currDirectory));

        if (chdir(args[1]) < 0)
        {
            perror("Error");
            return;
        }
        strcpy(prevDirectory, currDirectory);
    }
    else 
    {
        getcwd(currDirectory, sizeof(currDirectory));
        
        if (chdir(args[1]) < 0)
        {
            perror("error: No such directory exists\n");
            return;
        }
        strcpy(prevDirectory, currDirectory);
    }
}