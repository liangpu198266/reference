//this is the sender for msg example,in order to get clean message
//you need to run this in another shell differnet from the recevier

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

#define MAX_TEXT 512
struct my_msg_st
{
	int my_msg_type;
	char msg_text[MAX_TEXT];
};

int main(int argc,char *argv[])
{
	int running=1;
	struct my_msg_st some_data;
	int msgid;
	char buffer[BUFSIZ];
	
	if((msgid=msgget((key_t)12345,0666|IPC_CREAT))==-1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("Enter the mssage to send:");
		fgets(buffer,BUFSIZ,stdin);
		some_data.my_msg_type=1;
		strcpy(some_data.msg_text,buffer);

		if((msgsnd(msgid,(void *)&some_data,MAX_TEXT,0))==-1)
		{
			perror("msgsnd");
			exit(EXIT_FAILURE);
		}
		if(strncmp(buffer,"end",3)==0)
		{
			running=0;
		}
	}
	return 0;
}
