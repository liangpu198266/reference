#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	FILE *fp_src,*fp_des;
	char buf[128];
	int num;
	if(argc!=3)
	{
		printf("the format must be:cp file_src file_des");
		exit(EXIT_FAILURE);
	}
	if((fp_src=fopen(argv[1],"r"))==NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	if((fp_des=fopen(argv[2],"w"))==NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	do
	{
		num=fread(buf,1,128,fp_src);
		fwrite(buf,1,num,fp_des);
		//fwrite(buf,1,num,stdout);
	}while(num==128);
	fclose(fp_src);
	fclose(fp_des);
}
