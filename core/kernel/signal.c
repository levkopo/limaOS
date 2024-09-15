#include <signal.h>
#include <setjmp.h>

jmp_buf* signals_buffer;

int raise(int sig) {
    longjmp(signals_buffer, sig);
}

void (*signal(int sig, void (*handler) (int))) (int) {
    if(setjmp(signals_buffer) == sig) {
        handler(sig);
    }
}