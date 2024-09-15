#include <signal.h>

void assert(int expression) {
    if(!expression) {
        raise(SIGTERM); // TODO: make logs and normal exit
    }
}