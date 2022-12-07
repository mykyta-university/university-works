#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


int *buffer; 
int counter=0;
sem_t lock, empty_items, full_items;


void *producer(void *arg){
	srand(time(NULL));
    while(1){
    	    int value = (rand() % 10) + 1;
	    sem_wait(&empty_items); 		
	    sem_wait(&lock); 			
	    buffer[counter] = value;
	    counter++;
	    printf("Maker: %d\n", value);
	    sem_post(&lock);			
	    sem_post(&full_items); 		
	    sleep(1);				
    }
 	pthread_exit(NULL);
}

void *consumer(void *arg){
	while(1){
		sem_wait(&full_items); 		
		sem_wait(&lock);		
		counter--;
		printf("Consumer: %d\n", buffer[counter]);
		buffer[counter] = 0;
		sem_post(&lock);			
	  	sem_post(&empty_items); 		
	    	sleep(1);	
	}
	pthread_exit(NULL);
}

void *print(void *arg){
  int size = *(int*) arg;
  while (1) {
    for (int i = 0; i < size; i++){
      printf("%d ", buffer[i]);
    }  
    printf("\n");
    sleep(1);
  }
}

int main(int argc, char **argv){
	setbuf(stdout, NULL);
	int PRODUCE=1;
	int CONSUME=1;
	pthread_t *pr, *cn;
	int size = 10;
	if (argc > 1){
		size = atoi(argv[1]);
	}

	int check;
	buffer = malloc(sizeof(int) * size);
	
	check = sem_init(&lock, 0, 1);
	if (check != 0) {
		perror("Semaphore initialization failed.");
		exit(EXIT_FAILURE);
	}

	check = sem_init(&empty_items, 0, size);
	if (check != 0) {
		perror("Semaphore initialization failed.");
		exit(EXIT_FAILURE);
	}

	check = sem_init(&full_items, 0, 0);
	if (check != 0){
		perror("Semaphore initialization failed.");
		exit(EXIT_FAILURE);
	}		 

	pthread_attr_t attr;
  	pthread_t pt;
  	pthread_attr_init(&attr);
  	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 
  	pthread_create(&pt, &attr, &print, &size);
  	pthread_attr_destroy(&attr);

  	pr = malloc(sizeof(pthread_t) * PRODUCE);	
  	cn = malloc(sizeof(pthread_t) * CONSUME);	

   	for (int i = 0; i < PRODUCE; i++){
      	if (pthread_create(&pr[i], NULL, &producer, NULL) != 0) {		
        	fprintf(stderr, "Error thread\n");
        	return 1;
      	}
  	}

  	for (int i = 0; i < CONSUME; i++){
    	if (pthread_create(&cn[i], NULL, &consumer, NULL) != 0) {		
        	fprintf(stderr, "Error thread\n");
        	return 1;
      	}
  	}	

  	sleep(15);

	for(int i = 0; i < PRODUCE; ++i){			
		pthread_cancel(pr[i]);						
		if (pthread_join(pr[i], NULL) != 0) {
	      printf("Error\n");   
	    }
	}

  	for(int i = 0; i < CONSUME; ++i){
  		pthread_cancel(cn[i]);						
    	if (pthread_join(cn[i], NULL) != 0) {
      		printf("Error\n");   
    	}
  	}

  	pthread_cancel(pt);							

  	free(pr);
  	free(cn);
  	free(buffer);
  	sem_destroy(&lock);
  	sem_destroy(&empty_items);
  	sem_destroy(&full_items);
	return 0;
}
