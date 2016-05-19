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
    int max_priority,min_priority;
	pthread_t a_thread;
    void *thread_result;
    pthread_attr_t thread_attr;
	struct sched_param scheduling_value;

    res = pthread_attr_init(&thread_attr); 	//init attr
    if (res != 0) 
	{
        perror("Attribute creation failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setschedpolicy(&thread_attr, SCHED_OTHER);	//set policy is SCHED_OTHER
    if (res != 0) 
	{
        perror("Setting schedpolicy failed");
        exit(EXIT_FAILURE);
    }
    res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);	//set detachstate
    if (res != 0) 
	{
        perror("Setting detached attribute failed");
        exit(EXIT_FAILURE);
    }
	else
	printf("set the detachstate to PTHREAD_CREATE_DETACHED\n");
	
    res = pthread_create(&a_thread, &thread_attr, thread_function, (void *)message);	//create a new thread
    if (res != 0) 
	{
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
	else
		printf("create new thread success\n");
	
    max_priority = sched_get_priority_max(SCHED_OTHER);	//get max priority
    min_priority = sched_get_priority_min(SCHED_OTHER);	//get min priority
    printf("the max priority of SCHED_OTHRE is %d; the min is %d\n",max_priority,min_priority);
	
	res=pthread_attr_getschedparam(&thread_attr,&scheduling_value);
	if (res != 0)
	{   
		perror("get schedpolicy failed");
		exit(EXIT_FAILURE);
	}
	else
		printf("the priority of current thread is %d\n",scheduling_value.sched_priority);
	
	scheduling_value.sched_priority = -10;		//set sched priority
    res = pthread_attr_setschedparam(&thread_attr, &scheduling_value);
    if (res != 0) 
	{
        perror("Setting schedpolicy failed");
        exit(EXIT_FAILURE);
    }
	else
		printf("set the schedparam success\n");
	
	res=pthread_attr_getschedparam(&thread_attr,&scheduling_value);
	if (res != 0)
	{
		perror("get schedpolicy failed");
		 exit(EXIT_FAILURE);
	}
	else
		printf("the priority of current thread is %d\n",scheduling_value.sched_priority);
	
    (void)pthread_attr_destroy(&thread_attr);			//destory attr
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
