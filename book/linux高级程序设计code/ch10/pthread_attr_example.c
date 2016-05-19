#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "Hello World";
int thread_finished = 0;

int main(int argc,char argv[]) 
{
    int res;
	int state;
    pthread_t a_thread;
 //   void *thread_result;
    pthread_attr_t thread_attr;

    res = pthread_attr_init(&thread_attr);
    if (res != 0) 
	{
        perror("Attribute creation failed");
        exit(EXIT_FAILURE);
    }

	if((res = pthread_attr_getdetachstate(&thread_attr,&state))==-1)
	{
		perror("pthread_attr_getdetachstate");
		exit(EXIT_FAILURE);
	}
	else
		printf("The default detachstate is %d\n",state);

    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    if (res != 0) 
	{
        perror("Setting detached attribute failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, &thread_attr, thread_function, (void *)message);
    if (res != 0) 
	{
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
	if((res = pthread_attr_getdetachstate(&thread_attr,&state))==-1)
   	{
	        perror("pthread_attr_getdetachstate");
			exit(EXIT_FAILURE);
	}
	else 
		printf("now the thread's detachstate is %d\n",state);

    (void)pthread_attr_destroy(&thread_attr);
	sleep(2);
    while(!thread_finished) 

	{
        printf("Waiting for thread finished...\n");
        sleep(1);
    }
    printf("Other thread finished, bye!\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) 
{
	printf("thread_function is running. Argument was %s\n", (char *)arg);
    sleep(4);
    printf("Second thread setting finished flag, and exiting now\n");
    thread_finished = 1;
    pthread_exit(NULL);
}

