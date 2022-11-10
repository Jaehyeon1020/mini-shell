#define BUF_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * option1 : -n
 * option2 : K (몇 줄을 출력할 지)
*/
int myHead(char * option1, char * option2, char * file) {
    FILE * fp;
    char buf[BUF_SIZE];

    fp = fopen(file, "r");

    /* option이 있는 경우 : option 2만큼 라인을 파일의 위에서부터 출력 */
    if (option1 != NULL && option2 != NULL) {
        int lineNumberToPrint = atoi(option2);
        
        for (int i = 0; i < lineNumberToPrint; i++) {
            fgets(buf, BUF_SIZE, fp);
            fprintf(stdout, "%s", buf);
        }
    }

    /* option이 없는 경우 : file의 위에서부터 10 라인 표준 출력 */
    if (option1 == NULL && option2 == NULL) {
        for (int i = 0; i < 10; i++) {
            fgets(buf, BUF_SIZE, fp);
            fprintf(stdout, "%s", buf);
        }
    }

    fclose(fp);

    return 1;
}