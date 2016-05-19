#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
	int childpid;
	int id;
	int i;
	int buf[10];
	char *ptr;
	int totalbytes = 0;

	if((childpid = fork ())==-1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	
	if(childpid==0)
	{
		if ((id = shmget((key_t)12345,50*sizeof(char), IPC_CREAT)) == -1)
		{
			perror("Failed to create shared memory segment");
			exit(EXIT_FAILURE);
		}
		if ((ptr = (char *)shmat(id, NULL, 0)) == NULL)
		{
			if (shmctl(id, IPC_RMID, NULL) == -1)
				perror("Failed to  remove memory segment");
			exit(EXIT_FAILURE);
		}
		for(i=0;argv[1][i]!='\0';i++)
		{
			*ptr=argv[1][i];
			ptr++;
		}
		printf("this is child.\nwrite argv[1] to shm.\nyou input charater count is %d\n",i);
		exit(EXIT_SUCCESS);
	}
	
	else
	{
		wait(NULL);
		if ((id = shmget((key_t)12345, 50*sizeof(char), IPC_CREAT)) == -1)
		{
			perror("Failed to create shared memory segment");
			exit(EXIT_FAILURE);
		}
		if ((ptr = (char *)shmat(id, NULL, 0)) == NULL)
		{
			perror("shmat");
			if (shmctl(id, IPC_RMID, NULL) == -1)
				 perror("Failed to  remove memory segment");
			exit(EXIT_FAILURE);
		}
		printf("this is parent.\ninput charater is %s\n",ptr);
		
		if (shmctl(id, IPC_RMID, NULL) == -1)
		{
			perror("Failed to  remove memory segment");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}

		
