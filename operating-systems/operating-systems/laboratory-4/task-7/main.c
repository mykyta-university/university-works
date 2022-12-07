#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>

#define A 8
#define B 12
#define C 17
#define D 11
#define R 3

int main(int argc, char **argv){
  	pid_t status, childpid;
	int exit_status;
	int n = atoi(argv[1]);
	double m,s;
	printf("num: %d\n",n);

	status = fork();
	if (status == -1) {
		fprintf (stderr, "Fork Error\n");
		exit(EXIT_FAILURE);
	}

	if (status == 0){
		execl("count", argv[1], NULL);
		fprintf(stderr, "Exec Error\n");
		exit(EXIT_FAILURE);	
	}
	childpid = wait(&exit_status);
  	if (WIFEXITED(exit_status)) {			
		m = WEXITSTATUS(exit_status);
		s = (double) (m/n) * (B - A) * (C - D);
		printf("m = %.3f\n", m);
		printf("S = %.3f\n", s);
		printf("Pi: %.3f\n", s/(R*R));
	}
  return 0;
}
