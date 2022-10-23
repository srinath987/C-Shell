#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>

#include "takeinp.h"
#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "ls.h"
#include "discover.h"
#include "pinfo.h"
#include "fgbg.h"
#include "list.h"
#include "signal.h"
#include "history.h"
#include "jobs.h"
#include "sig.h"
#include "bg.h"
#include "fg.h"

char homeDirectory[1000];
pid_t homePID;
pid_t home_pgid;
char hostName[1000];
char currDirectory[1000];
char userName[1000];
char *allcmds[100];
char prevDirectory[1000];
char cwd[1000];
struct tm *t;

struct Node
{
    pid_t pid;
    char name[1000];
    int job_no;
    char stat[15];
    struct Node *next;
};
struct Node *head;

int err;

#endif