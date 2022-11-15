#ifndef _BUILTIN_CMD_H_
#define _BUILTIN_CMD_H_

#define BUF_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

void myCd(const char *path);
void myExit(int status);

#endif