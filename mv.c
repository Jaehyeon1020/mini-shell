#include "executable.h"

void myMv(char * source, char * destination) {
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

    rename(source, destination);
}