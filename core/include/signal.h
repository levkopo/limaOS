//
// Created by levkopo on 9/5/24.
//

#ifndef LIMAOS_SIGNALS_H
#define LIMAOS_SIGNALS_H
#define SIGTERM 1
#define SIGSEGV 2
#define SIGINT 3
#define SIGILL 4
#define SIGABRT 5
#define SIGFPE 6

int raise(int sig);
void (*signal( int sig, void (*handler) (int))) (int);

#endif //LIMAOS_SIGNALS_H
