#include "executable.h"

void myMv(char * source, char * destination) {
    /* 인자가 입력되지 않는 경우 */
    if (source == NULL) {
        printf("mv: missing file operand\n");
        return;
    }
    /* 인자가 하나만 입력되는 경우 */
    else if (destination == NULL) {
        printf("mv: missing destination file operand after %s\n", source);
        return;
    }

    if(rename(source, destination) != 0) {
        fprintf(stderr, "mv: %s\n", strerror(errno));
        exit(1);
    }
}

/* argv[0] : "mv" */
int main(int argc, char * argv[]) {
    /* 인자가 입력되지 않는 경우 */
    if (argc == 2) {
        myMv(NULL, NULL);
    }
    /* 인자가 한개만 입력되는 경우 */
    else if (argc == 3) {
        myMv(argv[1], NULL);
    }
    /* 모든 인자가 입력되는 경우 */
    else if (argc == 4) {
        myMv(argv[1], argv[2]);
    }

    return 0;
}