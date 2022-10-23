#include "discover.h"

void printContents(char *filePath, int f, int d, char *fileName, int fl)
{
    struct dirent **dir;
    int n = scandir(filePath, &dir, NULL, alphasort);

    struct stat statusBuffer;
    if (fl == 0)
    {
        if (f == 0 && d == 0)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                if (dir[i]->d_name[0] != '.')
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                        printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                        printf("%s%s\n", filePath, dir[i]->d_name);

                    strcpy(filePath2, filePath);
                    if (filePath[strlen(filePath) - 1] != '/')
                        strcat(filePath2, "/");
                    strcat(filePath2, dir[i]->d_name);
                    lstat(filePath2, &statusBuffer);

                    if ((statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                    {
                        printContents(filePath2, f, d, fileName, fl);
                    }
                }
                free(filePath2);
            }
        }
        else if (f == 1 && d == 0)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                strcpy(filePath2, filePath);
                if (filePath[strlen(filePath) - 1] != '/')
                    strcat(filePath2, "/");
                strcat(filePath2, dir[i]->d_name);
                lstat(filePath2, &statusBuffer);
                if (dir[i]->d_name[0] != '.' && ((statusBuffer.st_mode & S_IFMT) == S_IFREG))
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                        printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                        printf("%s%s\n", filePath, dir[i]->d_name);
                }
                if (dir[i]->d_name[0] != '.' && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    printContents(filePath2, f, d, fileName, fl);
                }
                free(filePath2);
            }
        }
        else if (f == 0 && d == 1)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                strcpy(filePath2, filePath);
                if (filePath[strlen(filePath) - 1] != '/')
                    strcat(filePath2, "/");
                strcat(filePath2, dir[i]->d_name);
                lstat(filePath2, &statusBuffer);
                if (dir[i]->d_name[0] != '.' && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                    printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                    printf("%s%s\n", filePath, dir[i]->d_name);
                    printContents(filePath2, f, d, fileName, fl);
                }
                free(filePath2);
            }
        }
        else if (f == 1 && d == 1)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                strcpy(filePath2, filePath);
                if (filePath[strlen(filePath) - 1] != '/')
                    strcat(filePath2, "/");
                strcat(filePath2, dir[i]->d_name);
                lstat(filePath2, &statusBuffer);
                if (dir[i]->d_name[0] != '.' && ((statusBuffer.st_mode & S_IFMT) == S_IFREG || (statusBuffer.st_mode & S_IFMT) == S_IFDIR))
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                    printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                    printf("%s%s\n", filePath, dir[i]->d_name);
                }
                if (dir[i]->d_name[0] != '.' && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    printContents(filePath2, f, d, fileName, fl);
                }
                free(filePath2);
            }
        }
    }
    else if (fl == 1)
    {
        if (f == 0 && d == 0)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                if (strcmp(dir[i]->d_name, fileName) == 0)
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                    printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                    printf("%s%s\n", filePath, dir[i]->d_name);
                }
                strcpy(filePath2, filePath);
                if (filePath[strlen(filePath) - 1] != '/')
                    strcat(filePath2, "/");
                strcat(filePath2, dir[i]->d_name);
                lstat(filePath2, &statusBuffer);

                if (dir[i]->d_name[0] != '.' && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    printContents(filePath2, f, d, fileName, fl);
                }
                free(filePath2);
            }
        }
        else if (f == 1 && d == 0)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                strcpy(filePath2, filePath);
                if (filePath[strlen(filePath) - 1] != '/')
                    strcat(filePath2, "/");
                strcat(filePath2, dir[i]->d_name);
                lstat(filePath2, &statusBuffer);
                if (strcmp(dir[i]->d_name, fileName) == 0 && (statusBuffer.st_mode & S_IFMT) == S_IFREG)
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                    printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                    printf("%s%s\n", filePath, dir[i]->d_name);
                }
                if (dir[i]->d_name[0] != '.' && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    printContents(filePath2, f, d, fileName, fl);
                }
                free(filePath2);
            }
        }
        else if (f == 0 && d == 1)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                strcpy(filePath2, filePath);
                if (filePath[strlen(filePath) - 1] != '/')
                    strcat(filePath2, "/");
                strcat(filePath2, dir[i]->d_name);
                lstat(filePath2, &statusBuffer);
                if (strcmp(dir[i]->d_name, fileName) == 0 && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                    printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                    printf("%s%s\n", filePath, dir[i]->d_name);
                }
                if (dir[i]->d_name[0] != '.' && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    printContents(filePath2, f, d, fileName, fl);
                }
                free(filePath2);
            }
        }
        else if (f == 1 && d == 1)
        {
            char *filePath2;
            for (int i = 0; i < n; i++)
            {
                filePath2 = (char *)malloc(150 * sizeof(char));
                strcpy(filePath2, filePath);
                if (filePath[strlen(filePath) - 1] != '/')
                    strcat(filePath2, "/");
                strcat(filePath2, dir[i]->d_name);
                lstat(filePath2, &statusBuffer);
                if (strcmp(dir[i]->d_name, fileName) == 0 && ((statusBuffer.st_mode & S_IFMT) == S_IFREG || (statusBuffer.st_mode & S_IFMT) == S_IFDIR))
                {
                    if (filePath[strlen(filePath) - 1] != '/')
                    printf("%s/%s\n", filePath, dir[i]->d_name);
                    else
                    printf("%s%s\n", filePath, dir[i]->d_name);
                }
                if (dir[i]->d_name[0] != '.' && (statusBuffer.st_mode & S_IFMT) == S_IFDIR)
                {
                    printContents(filePath2, f, d, fileName, fl);
                }
                free(filePath2);
            }
        }
    }
}

void discover(char **args)
{
    int f = 0, d = 0;
    char *targetDirectory;
    int targetGiven = 0;
    targetDirectory = malloc(150 * sizeof(char));
    char *fileName;
    fileName = (char *)malloc(150 * sizeof(char));
    int flNameGiven = 0;

    for (int i = 1; args[i] != NULL; i++)
    {
        if (args[i][0] != '"' && strcmp(args[i], "-d") != 0 && strcmp(args[i], "-f") != 0 && strcmp(args[i], "~") != 0)
        {
            targetDirectory = args[i];
            targetGiven = 1;
        }
        else if (strcmp(args[i], "~") == 0)
        {
            targetDirectory = homeDirectory;
            targetGiven = 1;
        }
        else if (strcmp(args[i], "-d") == 0)
        {
            d = 1;
        }
        else if (strcmp(args[i], "-f") == 0)
        {
            f = 1;
        }
        else if (args[i][0] == '"')
        {
            args[i][strlen(args[i]) - 1] = '\0';
            strcpy(fileName, args[i] + 1);
            flNameGiven = 1;
        }
    }

    if (targetGiven == 0)
    {
        targetDirectory = ".";
    }
    else if (!checkIfFileExists(targetDirectory))
    {
        targetDirectory = ".";
    }

    printContents(targetDirectory, f, d, fileName, flNameGiven);
}
