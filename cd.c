#include "builtin_cmd.h"

void myCd(const char * path) {
    if(chdir(path) == -1) {
        fprintf(stderr, "cd: %s\n", strerror(errno));
        exit(1);
    }
}