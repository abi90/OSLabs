/* Sample program to handle system signals */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void * myhandler(int myint)
{
   printf("\nSignal Handled!!\nCaugth signal:%d\n",myint);
   exit(0);
}

int main()
{
   signal( SIGINT, (void *)  myhandler );
   signal( SIGTERM, (void *)  myhandler );
   while(1) {
	printf("Doing Nothing...\n");
	sleep(10);

   }
}
