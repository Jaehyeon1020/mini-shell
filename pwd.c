#include "executable.h"

void myPwd() {
    char buf[BUF_SIZE];

    getcwd(buf, BUF_SIZE);
    printf("%s\n",buf);
}