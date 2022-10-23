#include "main.h"

#ifndef __LS_H
#define __LS_H

void ls(char **args);
int checkIfFileExists(const char *filename);
void print_details(char *pathName, char *dirName);

#endif