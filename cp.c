#include "executable.h"

void myCp(char * source, char * destination) {
    int sourceFd;
    int destFd;
    int charNum;
    char buf[BUF_SIZE];

    /* 인자가 입력되지 않는 경우 */
    if (source == NULL) {
        printf("cp: missing file operand\n");
        return;
    }
    /* 인자가 하나만 입력되는 경우 */
    else if (destination == NULL) {
        printf("cp: missing destination file operand after %s\n", source);
        return;
    }
    
    if ((sourceFd = open(source, O_RDONLY)) < 0) {
        fprintf(stderr, "cp: %s\n", strerror(errno));
        exit(1);
    }

    if ((destFd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        fprintf(stderr, "cp: %s\n", strerror(errno));
        exit(1);
    }

    /* 파일 복사 */
    while ((charNum = read(sourceFd,buf,BUF_SIZE)) > 0) {
        write(destFd, buf, charNum);
    }

    close(sourceFd);
    close(destFd);
}