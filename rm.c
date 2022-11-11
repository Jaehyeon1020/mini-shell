#include "executable.h"

void myRm(char * file) {
    if (unlink(file) == -1) {
        fprintf(stderr, "rm: %s\n", strerror(errno));
    }
}