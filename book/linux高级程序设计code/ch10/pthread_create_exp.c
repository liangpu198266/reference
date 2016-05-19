#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct message
{
	int i;
	int j;
};


void *hello(struct message *str)
{
	printf("the arg.i is %d\n",str->i);
	printf("the arg.j is %d\n",str->j);
}

int main(int argc,char *agrv[])
{
	struct message test;
	pthread_t thread_id;
	test.i=10;
	test.j=20;
	pthread_create(&thread_id,NULL,(void *)*hello,&test);
	printf("the new thread id is %u\n",thread_id);	
	pthread_join(thread_id,NULL);
}
