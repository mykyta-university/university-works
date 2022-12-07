#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#define TIME 3	

int main(void) {
	pid_t pid;
	int counter = 0;
	time_t t = time(NULL) + TIME;
	pid = fork();
	while (t > time(NULL)) {
		counter++;
	}
	if (pid == 0) {
		printf("child process complete = %d times.\n", counter);
	} else if (pid > 0) {
		printf("parent process complete  = %d times.\n", counter);
	} else {
		printf("Error\n"); 
	}
	return EXIT_SUCCESS;
}
