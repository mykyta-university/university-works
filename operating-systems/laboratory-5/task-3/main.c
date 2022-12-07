#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

struct thread_arg1 {
	char * str;
	int num;
};

struct thread_arg2 {
	int min;
	int max;
	int num;
	int close;
};

void * func1(void * arg) {
	struct thread_arg1 targ = *(struct thread_arg1 *) arg;
	for (int i = 1; i <= targ.num; i++){
		printf("Child thread: %s Iteration %d.\n\n", targ.str, i);
		sleep(1);
	}
}

void * func2(void * arg) {
	struct thread_arg2 targ = *(struct thread_arg2 *) arg;
	srand(time(NULL));
	for (int i = 1; i <= targ.num; i++){
  		int x = rand() % targ.max + 1;
  		if (x == targ.close){
  			printf("Invalid number: %d. Ending running of thread\n\n", targ.close);
  			pthread_exit(NULL);
  		}
  		printf("%d. Number: %d\n",i, x);
  		sleep(1);
	}
}

int main(void) {
	pthread_t thread1, thread2;	

	struct thread_arg1 targ1;
	struct thread_arg2 targ2;
	
	targ1.str = "Thread str";
	targ1.num = 5;
	
	targ2.num = 5;
	targ2.min = 1;
	targ2.max = 10;
	targ2.close = 5;

	if (pthread_create(&thread1, NULL, &func1, &targ1) != 0) {
		fprintf(stderr, "Error 1 thread\n");
		return 1;
	}
	
	if (pthread_create(&thread2, NULL, &func2, &targ2) != 0) {
		fprintf(stderr, "Error 2 thread\n");
		return 1;
	}
	
	if (pthread_join(thread1, NULL) != 0) {
		fprintf(stderr, "Join error\n");
		return 1;		
	}

	if (pthread_join(thread2, NULL) != 0) {
		fprintf(stderr, "Join error\n");
		return 1;		
	}
	printf("All threads are ended\n");
	return 0;
}
