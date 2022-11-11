#include "executable.h"

void myCat(char * file) {
    FILE * fp;
    char buf[BUF_SIZE];

    /* file open: file 없는 경우에는 표준 입력 읽어서 표준 출력으로 출력 */
    if ((fp = fopen(file, "r")) == NULL) {
        fgets(buf, BUF_SIZE, stdin);
        fputs(buf, stdout);
        return;
    }

    fread(buf, sizeof(buf), 1, fp);
    printf("%s", buf);
}