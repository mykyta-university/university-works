#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#define A 8
#define B 12
#define C 17
#define D 11
#define X 3
#define Y 4
#define R 3

int main(int argc, char *argv[]){
	int x, y;
	int sum = 0;
	srand(time(NULL));
	for (int i = 0; i < atoi(argv[0]);i++){
		x = rand() % (A + 1);
		y = rand() % (B + 1);
		if ((A < x < B) && (C < y < D)){
			sum++;
		} 
	}
	exit(sum);
}
