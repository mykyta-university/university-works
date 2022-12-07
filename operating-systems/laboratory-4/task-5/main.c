#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>


void syst(char *comand){
	pid_t status, childpid;
	int exit_status;


	status = fork();
	if (status == -1) {
		fprintf (stderr, "Fork Error\n");
		exit(EXIT_FAILURE);
	}

	if (status == 0){
		execlp(comand, comand, NULL);
		fprintf(stderr, "Exec Error\n");
		exit(EXIT_FAILURE);	
	}
	childpid = wait(&exit_status);
	if( childpid == -1) {
		fprintf(stderr, "Wait Error\n");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(exit_status)) {			
		printf ("Process with PID=%d "
		"has exited with code=%d\n", childpid, WEXITSTATUS(exit_status));
	}
		
	if (WIFSIGNALED(exit_status)) {	
		printf ("Process with PID=%d "
		"has exited with signal \n", childpid);	
	}	
}


int main(int argc, char **argv) {
	if (argc == 1){
		printf("no args...\n");
	}
	if (argc == 2){
		syst(argv[1]);
	}
	
	return EXIT_SUCCESS;
}
