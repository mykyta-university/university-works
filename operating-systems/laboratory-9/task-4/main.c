#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int a = 1;

void handler(int signo, siginfo_t *si, void *context) { 
  if (signo == SIGUSR1){
    printf("%d. Taken SIGUSR1(%d).\n",a++, si->si_value.sival_int);
  }
}

int main(void) {
  pid_t pid, cpid;	
  int flag;
  struct sigaction sigAction;	
  union sigval value;		

  sigAction.sa_sigaction = handler;
  sigAction.sa_flags = SA_SIGINFO;		
						

  if (sigaction(SIGUSR1, &sigAction, 0) != 0) {			
    fprintf(stderr, "Error SIGINT!\n");
    exit(EXIT_FAILURE);
  }

  if (signal(SIGTERM, SIG_DFL) == SIG_ERR) {	
    fprintf(stderr, "Error SIGINT!\n");
    exit(EXIT_FAILURE);
  }

  pid = fork(); 
  
  if (pid == 0) {	
      int i;
      for (i = 0; i < 10;i++){			        
	pause();  		
      }
  } 
  
  if (pid > 0) {
    int i;   
    for (i = 0; i < 10; i++){
      value.sival_int = i;
      sigqueue(pid, SIGUSR1, value);		
	sleep(1);
    }
    kill(pid, SIGTERM);		
    cpid = wait(&flag);		
    printf("Child process exit.\n");
  }
	
	

  return 0;
}
