#include "execute.h"

void execute(char *arr)
{
    err = 0;
    int r = 0, s = 0;
    char *args[100] = {NULL};
    char *token = strtok(arr, " \t");
    if (token != NULL)
    {
        args[0] = token;
    }
    int k = 1;
    while (token != NULL)
    {
        token = strtok(NULL, " \t");
        if (token != NULL)
        {
            args[k] = token;
            k = k + 1;
        }
    }
    int and = 0;
    int numOfArgs = 0;
    for (int i = 0; args[i] != NULL; i++)
    {
        numOfArgs += 1;
    }

    if (strcmp(args[numOfArgs - 1], "&") == 0)
    {

        and = 1;
        args[numOfArgs - 1] = NULL;
    }

    if (!strcmp(args[0], "quit"))
    {
        exit(0);
    }

    else if (!strcmp(args[0], "cd"))
    {
        cd(args);
    }
    else if (!strcmp(args[0], "echo"))
    {
        echo(args);
    }
    else if (!strcmp(args[0], "pwd"))
    {
        pwd();
    }
    else if (!strcmp(args[0], "ls"))
    {
        ls(args);
    }
    else if (!strcmp(args[0], "pinfo"))
    {
        pinfo(args, numOfArgs);
    }
    else if (!strcmp(args[0], "discover"))
    {
        discover(args);
    }
    else if (!strcmp(args[0], "history"))
    {
        printHistory();
    }
    else if (!strcmp(args[0], "jobs"))
    {
        if (args[1])
        {
            if (!strcmp(args[1], "-r"))
                r = 1;
            else if (!strcmp(args[1], "-s"))
                s = 1;
        }
        jobs(r, s);
    }
    else if (!strcmp(args[0], "sig"))
    {
        if (numOfArgs != 3)
        {
            err = 1;
            printf("Invalid no.of arguments\n");
        }
        else
        {
            int p = atoi(args[1]);
            int q = atoi(args[2]);
            sig(p, q);
        }
    }
    else if (!strcmp(args[0], "bg"))
    {
        if (numOfArgs != 2)
            printf("invalid no.of arguments");
        int job_no = atoi(args[1]);
        bg(job_no);
    }
    else if (!strcmp(args[0], "fg"))
    {
        if (numOfArgs != 2)
            printf("invalid no. of arguments");
        int job_no = atoi(args[1]);
        fg(job_no);
    }
    else
    {
        fgbg(args, and);
    }
}
