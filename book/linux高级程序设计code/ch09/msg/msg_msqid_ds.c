#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>


int main(int argc,char *argv[])
{
	key_t key;
	int msgid;
	struct msqid_ds buf;
	if((key=ftok(".",'A'))==-1)
	{
		perror("ftok");
		exit(EXIT_FAILURE);
	}

	if((msgid=msgget(key,0666|IPC_CREAT))==-1)
	{
		perror("msgget");
		exit(EXIT_FAILURE);
	}
	
	msgctl(msgid,IPC_STAT,&buf);
	
	printf("the key: %d\n,the uid:%d\n,the gid:%d\n,the cuid:%d\n,the cgid:%d\n,the mode:%o\n,the squence:\n",buf.msg_perm.__key,buf.msg_perm.uid,buf.msg_perm.gid,buf.msg_perm.cuid,buf.msg_perm.cgid,buf.msg_perm.mode,buf.msg_perm.__seq);

	printf("the max bytes is:%d\n",buf.msg_qbytes);

	msgctl(msgid,IPC_RMID,(struct msqid_ds *)0);
	return 0;
}
