#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>

#define FIFO "/tmp/fifo"
main()
{
        pid_t pid;
		char buffer[80];
        int fd;
        unlink(FIFO);           //if FIFO exit,del FIFO file
        mkfifo(FIFO,0744);
        if(pid=fork()>0)
        {
                char s[]="Hello!";
                fd=open(FIFO,O_WRONLY);
  				printf("this is father write data is %s\n",s);
				printf("father's pid is %d\n",getpid());
  				write(fd,s,sizeof(s));
                close(fd);
				exit(EXIT_SUCCESS);
        }
		else if(pid==0)
        {
                sleep(2);
				fd=open(FIFO,O_RDONLY);
                read(fd,buffer,80);
  				printf("this is child read data is:%s\n",buffer);
                close(fd);
				printf("child's pid is %d\n",getpid());
				
				exit(EXIT_SUCCESS);
        }
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
}

