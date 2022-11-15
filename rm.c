#include "executable.h"

void myRm(char * file) {
    if (unlink(file) == -1) {
        fprintf(stderr, "rm: %s\n", strerror(errno));
        exit(1);
    }
}

/* argv[0] : "rm" */
int main(int argc, char * argv[]) {
    myRm(argv[1]);

    return 0;
}