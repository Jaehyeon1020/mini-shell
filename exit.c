#include "builtin_cmd.h"

void myExit(int status) {
    fprintf(stderr, "exit\n");
    exit(status);
}