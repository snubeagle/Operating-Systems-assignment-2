#include <assert.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int ppid = getppid();
    assert (kill(ppid, 23) != -1);
    assert (kill(ppid, 10) != -1);
    assert (kill(ppid, 12) != -1);

    assert (kill(ppid, 10) != -1);
    assert (kill(ppid, 10) != -1);
    
    return 0;
}