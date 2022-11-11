#define BUF_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void myTail(char * option1, char * option2, char * file) {
    FILE * fp;
    char buf[BUF_SIZE];

    /* file open: file 없는 경우에는 표준 입력 읽어서 표준 출력으로 출력 */
    if ((fp = fopen(file, "r")) == NULL) {
        fgets(buf, BUF_SIZE, stdin);
        fputs(buf, stdout);
        return;
    }

    /* 파일 끝으로 위치 이동 */
    fseek(fp, -1, SEEK_END);
    
    /* 개행문자 나올 때까지 거꾸로 탐색 */
    while (strcmp(buf, "\n") != 0) {
        fread(buf, sizeof(char), 1, fp);
        fseek(fp, -2, SEEK_CUR);
    }
    fseek(fp, 2, SEEK_CUR);

    /* option이 있는 경우: $option2 line 출력 */
    if (strcmp(option1, "-n") == 0) {
        int op2 = atoi(option2);

        for (int i = 0; i < op2; i++) {
            fgets(buf, BUF_SIZE, fp);
            printf("%s", buf);
            
            /* 앞줄로 이동 */
            fseek(fp, -2, SEEK_CUR);
            for (int j = 0; j < 2; j++) {
                while (strcmp(buf, "\n") != 0) {
                    fread(buf, sizeof(char), 1, fp);
                    fseek(fp, -2, SEEK_CUR);
                }
                fread(buf, sizeof(char), 1, fp);
                fseek(fp, -2, SEEK_CUR);
            }
        }
    }
    /* option이 없는 경우 : 10 line 출력 */
    else {
        for (int i = 0; i < 10; i++) {
            fgets(buf, BUF_SIZE, fp);
            printf("%s", buf);
            
            /* 앞줄로 이동 */
            fseek(fp, -2, SEEK_CUR);
            for (int j = 0; j < 2; j++) {
                while (strcmp(buf, "\n") != 0) {
                    fread(buf, sizeof(char), 1, fp);
                    fseek(fp, -2, SEEK_CUR);
                }
                fread(buf, sizeof(char), 1, fp);
                fseek(fp, -2, SEEK_CUR);
            }
        }
    }

    fclose(fp);
}