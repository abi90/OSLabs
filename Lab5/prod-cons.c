#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 20

int count = 0;
int in = 0;
int out = 0;
int buffer [BUFFER_SIZE];

pthread_t tid;

void insert(int item){
   while (count == BUFFER_SIZE);
   buffer[in] = item;
   in = (in + 1) % BUFFER_SIZE;
   count++;
}

int remove_item(){
   int item;
   while (count == 0);
   item = buffer[out];
   out = (out + 1) % BUFFER_SIZE;
   count--;
   return item;
}

void * producer(void * param){
   int item;
   while(1){
      item = rand() % BUFFER_SIZE ;
      insert(item);
      printf("inserted: %d\n", item);
   }
}

void * consumer(void * param){
   int item;
   while(1){
   item = remove_item();
   printf("removed: %d\n", item);
   }
}

int main(int argc, char * argv[])
{
    pthread_t ptid, ctid;
    pthread_attr_t p_attr, c_attr;

    pthread_attr_init(&p_attr);
    pthread_attr_init(&c_attr);

    pthread_attr_setscope(&p_attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&c_attr, PTHREAD_SCOPE_PROCESS);

    pthread_attr_setschedpolicy(&p_attr, SCHED_FIFO);
    pthread_attr_setschedpolicy(&c_attr, SCHED_RR);

    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);

    int i;

    for (i = 0; i < producers; i++)
       pthread_create(&tid, &p_attr, producer,NULL);

    for (i = 0; i < consumers; i++)
       pthread_create(&tid, &c_attr, consumer, NULL);  
    pthread_join(tid,NULL);
}

