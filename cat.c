#include "executable.h"

void myCat(char * file) {
    FILE * fp;
    char buf[BUF_SIZE];

    /* file open: file 없는 경우에는 표준 입력 읽어서 표준 출력으로 출력 */
    if ((fp = fopen(file, "r")) == NULL) {
        if (fgets(buf, BUF_SIZE, stdin) == NULL) {
            fprintf(stderr, "cat: %s\n", strerror(errno));
            exit(1);
        }

        if (fputs(buf, stdout) == EOF) {
            fprintf(stderr, "cat: %s\n", strerror(errno));
            exit(1);
        }
        return;
    }

    fread(buf, sizeof(buf), 1, fp);
    printf("%s\n", buf);
}

/* argv[0] : "cat" */
int main(int argc, char * argv[]) {
    myCat(argv[1]);
    return 0;
}