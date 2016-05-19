#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
void *thread_one()
{
	printf("thread_one id is %u\n",pthread_self());
}


void *thread_two()
{
	printf("thread_two id is %u\n",pthread_self());
}


int main(int argc,char *agrv[])
{
	pid_t pid;
	pthread_t tid_one,tid_two;
	if((pid=fork())==-1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0)
	{
		pthread_create(&tid_one,NULL,(void *)thread_one,NULL);
		pthread_join(tid_one,NULL);
	}

	else
	{
		pthread_create(&tid_two,NULL,(void *)thread_two,NULL);
		pthread_join(tid_two,NULL);
	}
	wait(NULL);
}
