//-----------------------------------------------------------
//
// SWE2024 : System Programming Experiment (Fall 2022)
//
// Skeleton Code for PA#2
//
// CSI, Sungkyunkwan University
//
//-----------------------------------------------------------


/* $ begin shellmain */
#define MAXARGS   128
#define MAXLINE	  256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "builtin_cmd.h"
#include "executable.h"

/* function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 

int main() 
{
    char cmdline[MAXLINE]; /* Command line */
    char *ret;

	signal(SIGINT,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);

    while (1) {
	/* Read */
	printf("mini> ");                   
	ret = fgets(cmdline, MAXLINE, stdin); 
	if (feof(stdin) || ret == NULL)
	    exit(0);

	/* Evaluate */
	eval(cmdline);
    } 
}
/* $end shellmain */
  
/*
 * $ begin eval
 * eval - Evaluate a command line
 * 1. 명령어 개수 파악
 * 2. 백그라운드 수행 여부 파악
 * 3. Input/Output redirection이 사용되었는지 파악
 * 4. 명령어 종류를 분석하여
 * 4-1. 직접 구현한 경우 자식 프로세스를 생성하여 수행
 * 4-2. 구현하지 않은 경우 자식 프로세스를 생성해 해당 프로그램을 실행
 * 5. 자식 프로세스를 생성한 경우 종료될때까지 기다림
 */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    int argc = 0;

    /* argv 널포인터로 초기화 */
    for (int i = 0; i < MAXARGS; i++) {
        argv[i] = NULL;
    }
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    /* 인자 개수 구하기 */
    for (int i = 0; i < MAXARGS; i++) {
        if (argv[i] != NULL) {
            argc += 1;
        } else {
            break;
        }
    }

    /* Ignore empty lines */
    if (argv[0] == NULL)
	return;

    /* builtin command가 아닌 경우 */
    /* 만약 builtin_command라면 if문 내부로 진입은 안되지만 커맨드 실행은 됨 (builtin_command 호출) */
    if (!builtin_command(argv)) { 
        /* Child runs user job */
        if ((pid = fork()) == 0) {
            char pathSub[MAXLINE] = "/bin/";
            char pathSub2[MAXLINE] = "/usr/bin/";
            strcat(pathSub, argv[0]);
            strcat(pathSub2, argv[0]);

            // 구현 필요 없는 명령어들 실행: 경로가 /bin 인 경우
            if (strcmp(argv[0], "ls") == 0 || strcmp(argv[0], "grep") == 0) {
                if (execv(pathSub, argv) < 0) {
                fprintf(stderr,"%s: Command not found.\n", argv[0]);
                exit(0);
                }
            }
            // 구현 필요 없는 명령어들 실행: 경로가 /usr/bin 인 경우
            else if (strcmp(argv[0], "man") == 0 || strcmp(argv[0], "sort") == 0 || 
                    strcmp(argv[0], "awk") == 0 || strcmp(argv[0], "bc") == 0) {
                if (execv(pathSub2, argv) < 0) {
                fprintf(stderr,"%s: Command not found.\n", argv[0]);
                exit(0);
                }
            }
            // head 명령어 호출
            else if (strcmp(argv[0], "head") == 0) {
                // option이 있는 경우
                if (strcmp(argv[1], "-n") == 0) {
                    myHead("-n", argv[2], argv[3]);
                    exit(0);
                }
                // option이 없는 경우
                else {
                    myHead(NULL, NULL, argv[1]);
                    exit(0);
                }
            }
            // tail 명령어 호출
            else if (strcmp(argv[0], "tail") == 0) {
                /* option 없을 때*/
                if (argc == 2) {
                    myTail(NULL, NULL, argv[1]);
                    exit(0);
                }
                /* option 있을 때 */
                else {
                    myTail(argv[1], argv[2], argv[3]);
                    exit(0);
                }
            }
            // cat 명령어 호출
            else if (strcmp(argv[0], "cat") == 0) {
                myCat(argv[1]);
                exit(0);
            }
            // cp 명령어 호출
            else if (strcmp(argv[0], "cp") == 0) {
                /* 인자가 입력되지 않는 경우 */
                if (argc == 1) {
                    myCp(NULL, NULL);
                    exit(0);
                }
                /* 인자가 1개만 입력된 경우 */
                else if (argc == 2) {
                    myCp(argv[1], NULL);
                    exit(0);
                }
                /* 인자가 모두 입력된 경우 */
                else if (argc == 3) {
                    myCp(argv[1], argv[2]);
                    exit(0);
                }
            }
            // mv 명령어 호출
            else if (strcmp(argv[0], "mv") == 0) {
                /* 인자가 입력되지 않는 경우 */
                if (argc == 1) {
                    myMv(NULL, NULL);
                    exit(0);
                }
                /* 인자가 1개만 입력된 경우 */
                else if (argc == 2) {
                    myMv(argv[1], NULL);
                    exit(0);
                }
                /* 인자가 모두 입력된 경우 */
                else if (argc == 3) {
                    myMv(argv[1], argv[2]);
                    exit(0);
                }
            }
            // rm 명령어 호출
            else if (strcmp(argv[0], "rm") == 0) {
                myRm(argv[1]);
                exit(0);
            }
            // pwd 명령어 호출
            else if (strcmp(argv[0], "pwd") == 0) {
                myPwd();
                exit(0);
            }
            // ./ 으로 시작하는 파일 실행
            else if (argv[0][0] == '.' && argv[0][1] == '/') {
                char * filename = argv[0] + 2;
                execv(argv[0], &filename);
            }
            else {
                fprintf(stderr,"%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        /* Parent waits for foreground job to terminate */
        /* 백그라운드 작업이 아닌 경우 */
        if (!bg) {
            int status;
            if (waitpid(pid, &status, 0) < 0)
                printf("waitfg: waitpid error");
        }
        else {
            printf("%d %s", pid, cmdline);
        }
    } // end if (!builtin_command(argv))

    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (strcmp(argv[0], "cd") == 0) {
        myCd(argv[1]);
        return 1;
    }
    else if (strcmp(argv[0], "exit") == 0) {
        if (argv[1] == NULL) {
            myExit(0);
        }
        else {
            myExit(atoi(argv[1]));
        }
    }

    return 0; // return false
}
/* $end eval */

/* 
 *  $ begin parseline
 *  parseline - Parse the command line and build the argv array
 */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */

    /* Ignore leading spaces */
    while (*buf && (*buf == ' '))
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) { // 공백문자의 위치를 찾아서 delin에 저장
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;

	/* Ignore spaces */
	while (*buf && (*buf == ' '))
	       buf++;
    }
    argv[argc] = NULL;
    
    /* Ignore blank line */
    if (argc == 0)
	return 1;

    /* Should the job run in the background? */
    /* 마지막 명령어가 &라면 : (bg에 1 저장됨 / 아닌 경우에는 0 저장됨)*/
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}
/* $end parseline */


