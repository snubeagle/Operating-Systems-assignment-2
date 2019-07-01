#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include <signal.h>

void sigurg_hdl() {
	assert (printf("SIGURG received from child\n") != 0);
}

void sigusr_hdl() {
	assert (printf("SIGUSR1 received from child\n") != 0);
}

void sigusr2_hdl() {
	assert (printf("SIGUSR2 received from child\n") != 0);
}

void handler(int action1) {
	if ((action1 == 23) | (action1 == 10) | (action1 == 12)) {
		if (action1 == 23) {
			sigurg_hdl();
		}
		else if (action1 == 10) {
			sigusr_hdl();
		}
		else {
			sigusr2_hdl();
		}
	}
	else {
		assert (printf("Invalid signal received from child\n") != 0);
	}
}

int main(int argc, char *argv[]){
    int exit_stat, result, wstatus;
	
	struct sigaction action;
	action.sa_handler = handler;

	sigemptyset (&action.sa_mask);
	action.sa_flags = SA_RESTART;

	assert (sigaction (SIGUSR1, &action, NULL) == 0);
	assert (sigaction (SIGUSR2, &action, NULL) == 0);
	assert (sigaction (SIGURG, &action, NULL) == 0);
	

    int arrrrrrr = fork();
    
    if (arrrrrrr < 0){
		perror("Fork");
		void exit(int);
	}
	else if (arrrrrrr == 0) {
		assert ((result = execl("./child", "child", (char *)NULL)) > 0);	
		if (result < 0) {
			assert (printf("Error executing counter file") != 0);
			void exit(int);
		}
	}
    else
		assert (waitpid(arrrrrrr, &exit_stat, 0) > -1);
		if (WIFEXITED(0)) {
			assert (printf("Process %d exited with status %d\n", arrrrrrr, WEXITSTATUS(wstatus)) !=0);
		}
		else {
			assert (printf("Child exited with invalid status\n") != 0);
		}
    return 0;
}

