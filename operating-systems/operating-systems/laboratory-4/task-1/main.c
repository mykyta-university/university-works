#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void getProcessInf(void){
	printf("id current: %d\n", getpid());
	printf("id parent: %d\n", getppid());
	printf("id group: %d\n", getpgrp());
	printf("id real owner: %d\n", getuid());
	printf("eUID: %d\n", geteuid());
	printf("id group real: %d\n", getgid());
	printf("eGID: %d\n", getegid());
}

int main(int argc, char **argv) {
	if(argc == 1) { 
		printf("no arg...\n");
		printf("arg list:\n");
		printf("-p 0 - process info.\n");
		printf("-p 1 - id current process and parent.\n");
		printf("-p 2 - id real owner.\n");
		printf("-p 3 - id real owner.\n");
		printf("-p 4 - id group.\n");		
		return 0;
	}
	char *optstring = "p:";
	int rez, a; 
	while((rez = getopt(argc, argv, optstring)) != -1) {
		switch(rez) {
			case 'p': 
			a = optarg[0];
			break;
			case '?': default: {
				printf("no arg...\n");
				printf("arg list:\n");
				printf("-p 0 - process info.\n");
				printf("-p 1 - id current process and parent.\n");
				printf("-p 2 - id real owner.\n");
				printf("-p 3 - id real owner.\n");
				printf("-p 4 - id group.\n");	
				break;
			};
		}
		switch(a) {
			case '0': 
				getProcessInf();
				break;
			case '1':
				printf("id current: %d\n", getpid());
				printf("id parent: %d\n", getppid());
				break;
			case '2': 
				printf("id real owner: %d\n", getuid());
				printf("id group real: %d\n", getgid());
				break;
			case '3':
				printf("eUID: %d\n", geteuid());
				printf("id group real: %d\n", getgid());
				break;
			case '4': 
				printf("id group: %d\n", getpgrp());
				break;
			case '?': default:{
				printf("no arg...\n");
				printf("arg list:\n");
				printf("-p 0 - process info.\n");
				printf("-p 1 - id current process and parent.\n");
				printf("-p 2 - id real owner.\n");
				printf("-p 3 - id real owner.\n");
				printf("-p 4 - id group.\n");	
				break;
			};
				
		}
	}
	return EXIT_SUCCESS;
}
