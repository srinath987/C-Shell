#include "ls.h"

int checkIfFileExists(const char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);
    if (exist == 0)
        return 1;
    else
        return 0;
}

void print_details(char *pathName, char *dirName)
{
    struct stat statusBuffer;
    if (lstat(pathName, &statusBuffer) < 0)
    {
        perror("failed");
    };

    if ((statusBuffer.st_mode & S_IFMT) == S_IFBLK)
        printf("b");
    else if ((statusBuffer.st_mode & S_IFMT) == S_IFLNK)
        printf("l");
    else if ((statusBuffer.st_mode & S_IFMT) == S_IFCHR)
        printf("c");
    else if ((statusBuffer.st_mode & S_IFMT) == S_IFDIR)
        printf("d");
    else if ((statusBuffer.st_mode & S_IFMT) == S_IFIFO)
        printf("f");
    else if ((statusBuffer.st_mode & S_IFMT) == S_IFREG)
        printf("-");
    else if ((statusBuffer.st_mode & S_IFMT) == S_IFSOCK)
        printf("s");

    printf("%c", (statusBuffer.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (statusBuffer.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (statusBuffer.st_mode & S_IXUSR) ? 'x' : '-');
    printf("%c", (statusBuffer.st_mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (statusBuffer.st_mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (statusBuffer.st_mode & S_IXGRP) ? 'x' : '-');
    printf("%c", (statusBuffer.st_mode & S_IROTH) ? 'r' : '-');
    printf("%c", (statusBuffer.st_mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (statusBuffer.st_mode & S_IXOTH) ? 'x' : '-');
    printf(" %4ld ", statusBuffer.st_nlink);
    
    printf("%10s ", getpwuid(statusBuffer.st_uid)->pw_name);
    printf("%10s ", getgrgid(statusBuffer.st_gid)->gr_name);
    
    printf("%10ld ", statusBuffer.st_size);
    
    char Time[1000];
    t = localtime(&statusBuffer.st_mtime);
    strftime(Time, sizeof(Time), "%b %e %Y %H:%M", t);
    printf("%s ", Time);
    char buf[1000];
    
    if ((statusBuffer.st_mode & S_IFMT) == S_IFLNK)
    {
        int i;
        if ((i = readlink(pathName, buf, sizeof(buf))) != -1)
        {
            buf[i] = '\0';
            printf("%s -> %s\n", dirName, buf);
        }
    }
    else
        printf("%s\n", dirName);
}

void ls(char **args)
{
    struct dirent **d;
    int l = 0, a = 0;
    char *Directories[100] = {NULL};
    int j = 0;

    for (int i = 1; args[i] != NULL; i++)
    {
        if (l == 0 && a == 0 && (strcmp(args[i], "-la") == 0 || strcmp(args[i], "-al") == 0))
        {
            l = 1;
            a = 1;
        }
        else if (l == 0 && strcmp(args[i], "-l") == 0)
        {
            l = 1;
        }
        else if (a == 0 && strcmp(args[i], "-a") == 0)
        {
            a = 1;
        }
        else if (strcmp(args[i], "~") == 0)
        {
            Directories[j] = homeDirectory;
            j++;

            if (j >= 100)
            {
                perror("Error : Exceeded number of arguments for command ls");
                return;
            }
        }
        else if (Directories[j] == NULL && strcmp(args[i], "&") != 0 && strcmp(args[i], "-l") != 0 && strcmp(args[i], "-a") != 0 && strcmp(args[i], "-la") != 0 && strcmp(args[i], "-al") != 0)
        {
            if (j > 100)
            {
                perror("Error : Exceeded number of arguments for command ls");
                return;
            }

            Directories[j] = args[i];
            j++;
        }
    }

    if (j == 0)
    {
        Directories[j] = ".";
    }

    for (int i = 0; i <= j; i++)
    {
        if (j > 0 && i == j)
            break;
        int n = scandir(Directories[i], &d, NULL, alphasort);

        if (n < 0)
        {
            if (!checkIfFileExists(Directories[i]))
            {
                printf("%s: No such file or directory\n", Directories[i]);
                continue;
            }
        }
        else
        {
            for(int k = 0; k < n; k++)
            {
                if ((a == 1) || (d[k]->d_name[0] != '.' && a == 0))
                {
                    if (l == 0)
                    {
                        printf("%s\n", d[k]->d_name);
                    }
                    else
                    {
                        char *filePath = (char *)malloc(sizeof(char) * 1000);
                        filePath[0] = '\0';
                        filePath = strcat(filePath, Directories[i]);
                        filePath = strcat(filePath, "/");
                        filePath = strcat(filePath, d[k]->d_name);
                        print_details(filePath, d[k]->d_name);
                    }
                }
                free(d[k]);
            }
            free(d);
        }
    }
}
