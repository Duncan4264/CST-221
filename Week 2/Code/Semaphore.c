#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mySemaphore;
char myString[60];
FILE* file;

void* threadOne (void* arg) {
   //wait
   sem_wait(&mySemaphore);
   //Critical Section
   strcpy(myString, "Shared Resource manipulated by first process.\n");
   sleep(2);
   printf("%s", myString);
	fprintf(file, "%s", myString);
   //Signal
   sem_post(&mySemaphore);
}

void* threadTwo (void* arg) {
   //wait
   sem_wait(&mySemaphore);
   //Critical Section
   strcpy(myString, "Second process accessing shared resource now.\n");
   sleep(2);
   printf("%s", myString);
	fprintf(file, "%s", myString);
   //Signal
   sem_post(&mySemaphore);
}

int main (){
	file = fopen("semaphore_output.txt", "w");
   sem_init(&mySemaphore, 0, 1);
   pthread_t thread1,thread2;
   pthread_create(&thread1,NULL,threadOne,NULL);
   sleep(2);
   pthread_create(&thread2,NULL,threadTwo,NULL);
   pthread_join(thread1,NULL);
   pthread_join(thread2,NULL);
   sem_destroy(&mySemaphore);
   return 0;
}







