#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int *mas;
int counter;
int num;

void * findNumber(void * arg) { 
     int value = *(int*) arg;
     printf("Thread sleep %d second.\n",value);
     sleep(value);
     srand(time(NULL));
     mas[value] = rand() % 10 + 1;
     num++;
     printf("Count thread : %d sleep %d sec.\n", value, mas[value]);
     sleep(mas[value]);
}

void* print(void* arg) {
	printf("\n");
	while (num<counter){
		for(int i = 0; i < counter; i++){
			printf("%d ", mas[i]);
		}
		printf("\n");
	printf("Discon. thead sleep 1 sec.\n");
	sleep(1);	
	}

	pthread_exit(NULL);
}


int main(int argc, char **argv){
	pthread_t *pt;
	if (argc == 1){
		printf("no arg\n");
	}else{
		counter = atoi(argv[1]);
		int num=0;
		mas = malloc (sizeof(int) * counter);
		pt = malloc (sizeof(pthread_t) * counter);

		int m[counter];
		for(int i=0;i<counter;i++){
			m[i]=i;
		}

		pthread_attr_t attr;
		pthread_t thr;
		pthread_attr_init (&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  
		pthread_create(&thr, &attr, &print, &counter); 
		pthread_attr_destroy (&attr);

		for (int i = 0; i < counter; i++){
			if (pthread_create(&pt[i], NULL, &findNumber, &m[i]) != 0) {
				fprintf(stderr, "Error thread)\n");
				return 1;
			}	
		}

		for(int i = 0; i < counter; i++){
			if (pthread_join(pt[i], NULL) == 0) {
				printf("Thread %d finished sucessfully.\n", i);		
			}
		}
	}
	free(mas);
	free(pt);
	return 0;
}
