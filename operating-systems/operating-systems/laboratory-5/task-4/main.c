#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int factorial (int n){
  return (n < 2) ? 1 : n * factorial (n - 1);
}

void * findNumber(void * arg) { 
	int size = *(int*) arg;
        int *a = (int*)malloc(size*sizeof(int));
   	for (int i = 0; i < size; i++){
   		a[i] = factorial(2*i)/(factorial(i + 1)*factorial(i));
   	}
   	pthread_exit((void *) a);
}

void * findSimpleNumber(void * arg) {		//решето Эратосфена
	int size = *(int*) arg;
	int *a = (int*)malloc(size*sizeof(int));
	for(int i = 0; i < size; i++){
           a[i] = i;
	    }
	    a[1] = 0;
	    for(int s = 2; s < size; s++){
		if(a[s] != 0){
		    for(int j = s*2; j < size; j += s){
		        a[j] = 0;
		    }
		}
	    }
	    pthread_exit((void*) a);
}

int main(void) {
	pthread_t thread1, thread2;	
	int firstTask = 5;
	int secondTask = 10;
	int *x, *y;

	if (pthread_create(&thread1, NULL, &findNumber, &firstTask) != 0) {
		fprintf(stderr, "Error 1 thread\n");
		return 1;
	}
	
	if (pthread_create(&thread2, NULL, &findSimpleNumber, &secondTask) != 0) {
		fprintf(stderr, "Error 2 thread\n");
		return 1;
	}
		
	pthread_join(thread1, (void **)&x);
	pthread_join(thread2, (void **)&y);

	printf("Числа Каталана(%d): ",firstTask);
	for(int i = 0;i < firstTask; i++){
		printf("%d ", x[i]);
	}
	printf("\nПростые числа от 0 до %d : ",secondTask);
	 for(int i = 0; i < secondTask; i++){
         if(y[i] != 0)
            printf("%d ", y[i]);
        }
	printf("\nAll threads finished...\n");
	free(x);
	free(y);
	return 0;
}
