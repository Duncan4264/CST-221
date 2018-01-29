#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t the_monitor;
char myString[60];

void* threadOne (void* arg) {
	//lock the monitor
    pthread_mutex_lock(&the_monitor);
    strcpy(myString, "Shared Resource manipulated by first process.");
    printf("%s\n", myString);
	//unlock monitor
    pthread_mutex_unlock(&the_monitor);
}

void* threadTwo (void* arg) {
	//Lock the monitor
    pthread_mutex_lock(&the_monitor);
    strcpy(myString, "Second process accessing shared resource now.");
    printf("%s\n", myString);
	//unlock the monitor
    pthread_mutex_unlock(&the_monitor);
}

int main (){
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,threadOne,NULL);
    sleep(2);
    pthread_create(&thread2,NULL,threadTwo,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
}
