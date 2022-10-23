#include "fgbg.h"
#include "prompt.h"

void fgbg(char **args, int and)
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
        perror("Error: \n");
    else if (pid == 0)
    {
        setpgid(0, 0);
        if (execvp(args[0], args) < 0)
        {
            perror("Error");
        }
    }
    else
    {
        if (and)
        {
            char name[1000];
            strcpy(name, args[0]);
            for (int i = 1; args[i] != NULL; i++)
            {
                strcat(name, " ");
                strcat(name, args[i]);
            }
            int job_num = 1;
            struct Node *temp = head;

            while (temp != NULL)
            {
                job_num = temp->job_no + 1;
                temp = temp->next;
            }

            insertNode(pid, name, job_num);

            printf("%d\n", pid);
        }
        else
        {
            int stat;
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            tcsetpgrp(0, pid);

            time_t rawtime;
            struct tm *timeinfo;

            time(&rawtime);
            timeinfo = localtime(&rawtime);
            waitpid(pid, &stat, WUNTRACED);

            time_t rawtime2;
            struct tm *timeinfo2;

            time(&rawtime2);
            timeinfo2 = localtime(&rawtime2);

            time_t const timediff = rawtime2 - rawtime;
            if (timediff >= 1)
            {
                printf("took %lds\n", timediff);
            }

            tcsetpgrp(0, homePID);
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);

            if (WIFSTOPPED(stat))
            {
                char name[1000];
                strcpy(name, args[0]);
                for (int i = 1; args[i] != NULL; i++)
                {
                    strcat(name, " ");
                    strcat(name, args[i]);
                }
                int job_num = 1;
                struct Node *temp = head;

                while (temp != NULL)
                {
                    job_num = temp->job_no + 1;
                    temp = temp->next;
                }

                insertNode(pid, name, job_num);
                printf("%s with PID %d is suspended\n", name, pid);
            }
        }
    }
}