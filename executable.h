#ifndef _EXECUTABLE_H_
#define _EXECUTABLE_H_

#define BUF_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

void myHead(char * option1, char * option2, char * file);
void myTail(char * option1, char * option2, char * file);
void myCat(char * file);
void myCp(char * source, char * destination);
void myMv(char * source, char * destination);
void myRm(char * file);
void myPwd();

#endif