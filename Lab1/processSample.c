/* Example of use of fork system call */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void main()
{
  int pid;
  
  pid = vfork();

  if (pid < 0) { /* error occurred */
	  fprintf(stderr, "Fork failed!\n");
	  exit(-1);
  }

  else if (pid==0) { /* child process */
	  printf("I am the child, return from fork=%d\n", pid);
	  execlp("/bin/ps", "ps", NULL);
  }
  else { /* parent process */
          wait(NULL);
	  printf("I am the parent, return from fork, child pid=%d\nParent pid=%d\n", pid,getpid());
	  printf("Parent exiting!\n");
	  exit(0);
  }
}
