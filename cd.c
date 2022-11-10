#include <unistd.h>

int myCd(const char * path) {
    int retval = chdir(path);

    return retval;
}