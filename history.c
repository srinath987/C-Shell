#include "history.h"

void writeHistory(char *cmd)
{
    char *historyFile;
    historyFile = (char *)malloc(1000 * sizeof(char));
    strcpy(historyFile, homeDirectory);
    strcat(historyFile, "/cmdHistory.txt");

    FILE *fp;
    fp = fopen(historyFile, "a+");

    char hist[21][1000];
    int count = 0;
    size_t chars = 0;
    size_t len = 0;
    char *line;

    while ((chars = getline(&line, &len, fp)) != -1)
    {
        line[chars - 1] = '\0';
        strcpy(hist[count], line);

        count++;
    }

    if (count < 20)
    {
        if (strcmp(line, cmd) != 0)
        {
            fprintf(fp, "%s\n", cmd);
        }
    }
    else
    {
        if (strcmp(line, cmd) != 0)
        {
            for (int i = 0; i < count - 1; i++)
                strcpy(hist[i], hist[i + 1]);

            strcpy(hist[count - 1], cmd);
        }

        fclose(fp);

        fp = fopen(historyFile, "w");

        for (int i = 0; i < count; i++)
            fprintf(fp, "%s\n", hist[i]);
    }

    fclose(fp);
}

void printHistory()
{
    char hist[21][1000];
    int count = 0;
    FILE *fp;

    char *historyFile;
    historyFile = (char *)malloc(1000 * sizeof(char));
    strcpy(historyFile, homeDirectory);
    strcat(historyFile, "/cmdHistory.txt");

    fp = fopen(historyFile, "r");
    if (fp == NULL)
    {
        perror("No previous history found!");
        return;
    }

    size_t chars = 0;
    size_t len = 0;
    char *line;

    while ((chars = getline(&line, &len, fp)) != -1)
    {
        line[chars - 1] = '\0';
        strcpy(hist[count], line);

        count++;
    }

    if (count <= 10)
    {
        for (int i = 0; i < count; i++)
            printf("%s\n", hist[i]);
    }
    else
    {
        for (int i = count - 10; i < count; i++)
            printf("%s\n", hist[i]);
    }

    fclose(fp);
}