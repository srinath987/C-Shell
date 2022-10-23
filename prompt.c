#include "prompt.h"

void initialize()
{
    getcwd(homeDirectory, sizeof(homeDirectory));
    getlogin_r(userName, sizeof(userName));
    gethostname(hostName, sizeof(hostName));
    head = NULL;
    signal(SIGCHLD, bgrndt);
    signal(SIGINT, ctrlC);
    signal(SIGTSTP, ctrlZ);

    prevDirectory[0] = '\0';
    currDirectory[0] = '\0';
    strcpy(currDirectory, homeDirectory);
    homePID = getpid();
}

void prompt()
{
    if (getcwd(currDirectory, sizeof(currDirectory)))
    {
        if (strstr(currDirectory, homeDirectory))
        {
            char *rel_path = strstr(currDirectory, homeDirectory) + strlen(homeDirectory);
            printf("<%s@%s:~%s>", userName, hostName, rel_path);
        }
        else
        {
            printf("<%s@%s:%s>", userName, hostName, currDirectory);
        }
    }
}