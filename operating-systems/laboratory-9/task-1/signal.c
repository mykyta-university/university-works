#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo) {
	if (signo == SIGINT)
		printf("Taken SIGINT!\n");
	else if (signo == SIGTERM)
		printf("Taken SIGTERM!\n");
	else if (signo == SIGUSR1)
		printf("Taken SIGUSR1!\n");
	else {
		fprintf(stderr, "Anexpected signal !\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}


int main (void) {
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Error SIGINT!\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGTERM, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Error SIGTERM!\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
		fprintf(stderr, "Error SIGUSR1!\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
		fprintf(stderr, "Error SIGPROF!\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
		fprintf(stderr, "Error SlGHUP!\n");
		exit(EXIT_FAILURE);
	}
	for (;;) {
		pause();
	}
	return 0;
}
