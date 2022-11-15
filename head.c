#include "executable.h"

/**
 * option1 : -n
 * option2 : K (몇 줄을 출력할 지)
*/
void myHead(char * option1, char * option2, char * file) {
    FILE * fp;
    char buf[BUF_SIZE];

    /* file open: file 없는 경우에는 표준 입력 읽어서 표준 출력으로 출력 */
    if ((fp = fopen(file, "r")) == NULL) {
        if (fgets(buf, BUF_SIZE, stdin) == NULL) {
            fprintf(stderr, "head: %s\n", strerror(errno));
            exit(1);
        }

        if (fputs(buf, stdout) == EOF) {
            fprintf(stderr, "head: %s\n", strerror(errno));
            exit(1);
        }
        return;
    }

    /* option이 없는 경우 : file의 위에서부터 10 라인 표준 출력 */
    if (option1 == NULL && option2 == NULL) {
        for (int i = 0; i < 10; i++) {
            fgets(buf, BUF_SIZE, fp);
            fprintf(stdout, "%s", buf);
        }
    }

    /* option -n이 있는 경우 : option 2만큼 라인을 파일의 위에서부터 출력 */
    if (strcmp(option1, "-n") == 0) {
        int lineNumberToPrint = atoi(option2);
        
        for (int i = 0; i < lineNumberToPrint; i++) {
            fgets(buf, BUF_SIZE, fp);
            fprintf(stdout, "%s", buf);
        }
    }

    fclose(fp);
}

/* argv[0] : "head" */
int main(int argc, char * argv[]) {
    /* option이 있는 경우 */
    if (argc == 4) {
        myHead(argv[1], argv[2], argv[3]);
    }
    /* option 없는 경우 */
    else {
        myHead(NULL, NULL, argv[1]);
    }

    return 0;
}