/*
	Name: Ying Zhang, Kenny Jin
	NetID: yzhang865, jjin59
	CS login: yingzhang, kjin
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "thread_reader.h"
#include "Queue.h"
#include "thread_munch1.h"
#include "thread_munch2.h"
#include "thread_writer.h"

/* This is the main program which creates the four threads and three 
queues which would be parameters of the threads to help to realize 
the purposes
*/
int main() {

	Queue* queue1 = CreateStringQueue(10);
	Queue* queue2 = CreateStringQueue(10);
	Queue* queue3 = CreateStringQueue(10);

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	Queue** array_ptrs = malloc(2*sizeof(Queue*));
	array_ptrs[0] = queue1;
	array_ptrs[1] = queue2;
	Queue** array_ptrs_munch1 = malloc(2*sizeof(Queue*));
	array_ptrs_munch1[0] = queue2;
	array_ptrs_munch1[1] = queue3;

	// create thread_reader
	if(pthread_create(&thread1, NULL, thread_reader, (void*)queue1)) {
		fprintf(stderr, "Error creating thread1\n");
		return 1;
	}
	
	// create thread_munch1
	if(pthread_create(&thread2, NULL, thread_munch1, (void*)array_ptrs)) {
	 	fprintf(stderr, "Error creating thread2\n");
	 	return 1;
	}

	// create thread_munch2
	if(pthread_create(&thread3, NULL, thread_munch2, (void*)array_ptrs_munch1)) {
                fprintf(stderr, "Error creating thread3\n");
                return 1;
        }
	
	// create thread_writer
	if(pthread_create(&thread4, NULL, thread_writer, (void*)queue3)) {
                fprintf(stderr, "Error creating thread4\n");
                return 1;
        }

    // join thread_reader
	if(pthread_join(thread1, NULL)) {
		fprintf(stderr, "Error joining thread1\n");
	}

	// join thread_munch1
	if(pthread_join(thread2, NULL)) {
	 	fprintf(stderr, "Error joining thread2\n");
	}

	// join thread_munch2
	if(pthread_join(thread3, NULL)) {
                fprintf(stderr, "Error joining thread3\n");
    }

    // join thread_writer
	if(pthread_join(thread4, NULL)) {
                fprintf(stderr, "Error joining thread4\n");
    }
    
	printf("\n");
	printf("For queue 1:\n");
	PrintQueueStats(queue1);
	printf("\n");
	printf("For queue 2:\n");
	PrintQueueStats(queue2);
	printf("\n");
	printf("For queue 3:\n");
	PrintQueueStats(queue3);

}
