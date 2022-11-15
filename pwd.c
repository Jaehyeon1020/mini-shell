#include "executable.h"

void myPwd() {
    char buf[BUF_SIZE];

    getcwd(buf, BUF_SIZE);
    printf("%s\n",buf);
}

/* argv[0] : "pwd" */
int main(int argc, char * argv[]) {
    myPwd();

    return 0;
}