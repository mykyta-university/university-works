#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct threadStruct {
	char * name;
	char * str;
	int num;
};

void * any_func(void * arg) {
	struct threadStruct tStr = *(struct threadStruct *) arg;
	for (int i = 1; i <= tStr.num; i++){
		printf("Thread name: %s. Thread str: %s. Num of repetitions: %d\n",tStr.name, tStr.str, i );
		sleep(1);
	}
	return NULL;
}

int main(void) {
	pthread_t thread1, thread2, thread3, thread4;
	
	struct threadStruct tStr1;
	struct threadStruct tStr2;
	struct threadStruct tStr3;
	struct threadStruct tStr4;
	
	tStr1.name = "1 thread";
	tStr1.str = "1 thread str";
	tStr1.num = 1;
	
	tStr2.name = "2 thread";
	tStr2.str = "2 thread str";
	tStr2.num = 2;

	tStr3.name = "3 thread";
	tStr3.str = "3 thread str";
	tStr3.num = 3;

	tStr4.name = "4 thread";
	tStr4.str = "4 thread str";
	tStr4.num = 4;

	if (pthread_create(&thread1, NULL, &any_func, &tStr1) != 0) {
		fprintf(stderr, "Error 1 thread\n");
		return 1;
	}
	
	if (pthread_create(&thread2, NULL, &any_func, &tStr2) != 0) {
		fprintf(stderr, "Error 2 thread\n");
		return 1;
	}
	
	if (pthread_create(&thread3, NULL, &any_func, &tStr3) != 0) {
		fprintf(stderr, "Error 3 thread\n");
		return 1;
	}

	if (pthread_create(&thread4, NULL, &any_func, &tStr4) != 0) {
		fprintf(stderr, "Error 4 thread\n");
		return 1;
	}

	sleep(5);
	return 0;
};
