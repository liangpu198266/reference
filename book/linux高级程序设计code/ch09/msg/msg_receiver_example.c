//this is the receiver program
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct my_msg_st
{
	int my_msg_type;
	char msg_text[BUFSIZ];
};

int main(int argc,char *argv[])
{
	int running=1;
	int msgid;
	struct my_msg_st some_data;
	int msg_to_receive=0;


	if((msgid=msgget((key_t)12345,0666 | IPC_CREAT))==-1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		if(msgrcv(msgid,(void *)&some_data,BUFSIZ,msg_to_receive,0)==-1)
		{
			perror("msgrcv");
			exit(EXIT_FAILURE);
		}
		printf("receiver mssage:%s",some_data.msg_text);
		if(strncmp(some_data.msg_text,"end",3)==0)

			running=0;
	}

	if(msgctl(msgid,IPC_RMID,0)==-1)
	{
		fprintf(stderr,"msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
