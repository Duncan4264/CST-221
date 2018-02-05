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
pthread_mutex_t lock;
int buffer = 0;
int temp;
time_t t;
FILE* file;

void* produce(){
	temp = rand() % 50;
	printf("Producer is creating number: %d\n", temp);
	fprintf(file, "Producer is creating number: %d\n", temp);
}

void* put(){
    	
	pthread_mutex_lock(&lock);
	//Put thread to sleep while buffer is full
	while (buffer != 0)
		pthread_cond_wait(&condp, &lock);
	buffer = temp;
	temp = 0;
	//Wake up consumer thread
    	pthread_cond_signal(&condc);
	pthread_mutex_unlock(&lock);
}

void* producer(){
	int x = 0;
    while (x < 5){
	produce();
	put();
	x++;
    }
}

void* consume(){
	printf("Consumer is consuming number : %d\n", buffer);
    	fprintf(file, "Consumer is consuming number : %d\n", buffer);
}

void* get(){
	pthread_mutex_lock(&lock);
    //While buffer is empty, sleep thread
    	while (buffer == 0)
		pthread_cond_wait(&condc, &lock);
    //Wake up producer thread
	consume();
	buffer = 0;
    	pthread_cond_signal(&condp);
	pthread_mutex_unlock(&lock);
}

void* consumer(){
	int x = 0;
    while (x < 5){
	get();
	x++;
    }
}

int main(){
    srand((unsigned) time(&t));
	file = fopen("procon_output.txt", "w");
    //Create producer and consumer threads
    pthread_t proThread, conThread;
    //Initialize conditional threads
    pthread_cond_init(&condp, NULL);
    pthread_cond_init(&condc, NULL);
    //Initialize producer and consumer threads
    pthread_create(&proThread, NULL, producer, NULL);
    pthread_create(&conThread, NULL, consumer, NULL);
    //Join threads
    pthread_join(proThread, NULL);
    pthread_join(conThread, NULL);
}
