/*	
*	Author: Michael Weaver
	
	Attempt: A producer thread generates a random number while
	a consumer class retrieves it from a buffer and prints it
	to the console.
*/	

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_cond_t condc, condp;
int buffer = 0;

int produce(){
    return rand();
}

void put(int i){
    //Put thread to sleep while buffer is full
    while (buffer != 0)
	condp.sleep(25);
    buffer = i;
    //Wake up consumer thread
    condc.wakeup();
}

void* producer(void *ptr){
    int i;
    while (1){
	i = produce();
	put(i);
    }
}

void consume(int i){
    printf(“%i”, i);
}

int get(){
    //Temporary to store buffer
    int i = buffer;
    //While buffer is empty, sleep thread
    while (buffer == 0)
	condc.sleep(25);
    //After extracting buffer, set to 0
    buffer = 0;
    //Wake up producer thread
    condp.wakeup();
    //Pass stored buffer variable up
    return i;
}

void* consumer(void *ptr){
    int i;
    while (1){
	i = get();
	consume(i);
    }
}

int main(){
    //Create producer and consumer threads
    pthread_t proThread, conThread;
    //Initialize conditional threads
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);
    //Initialize producer and consumer threads
    pthread_create(&proThread, NULL, producer, NULL);
    pthread_create(&conThread, NULL, consumer, NULL);
    //Join threads
    pthread_join(&proThread);
    pthread_join(&conThread);
}
