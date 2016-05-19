#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

#define N_BITS 3

int is_dir(mode_t st_mode)
{
	return ((st_mode & S_IFMT) == S_IFDIR) ? 1 : 0;
}

int is_lnk(mode_t st_mode)
{
	return ((st_mode & S_IFMT) == S_IFLNK) ? 1 : 0;
}

char file_type(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFSOCK)
		return 's';
	else if ((st_mode & S_IFMT) == S_IFLNK)
		return 'l';
	else if ((st_mode & S_IFMT) == S_IFREG)
		return '-';
	else if ((st_mode & S_IFMT) == S_IFBLK)
		return 'b';
	else if ((st_mode & S_IFMT) == S_IFCHR)
		return 'c';
	else if ((st_mode & S_IFMT) == S_IFIFO)
		return 'p';
	else
		return 'd';
}

int print_perm(mode_t st_mode)
{
	int i;
	unsigned int mask = 0700;
	static char *perm[] = {"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"};
	for (i = 3; i; --i)
	{
		printf("%3s", perm[(st_mode & mask) >> (i - 1) * N_BITS]);
		mask >>= N_BITS;
	}
	return 0;
}

int list_file(struct stat buff)
{
	struct passwd *p_passwd;
	struct group *p_group;
	int i;
	char *p_time;

	p_time = ctime(&buff.st_mtime);
	p_passwd = getpwuid(buff.st_uid);	
	p_group = getgrgid(buff.st_gid);

	putchar(file_type(buff.st_mode));
	print_perm(buff.st_mode);
	printf(" %5d %s %s %7d ", buff.st_nlink, p_passwd->pw_name, p_group->gr_name, (int)buff.st_size);
	for (i = 0; p_time[i] != 0 && p_time[i] != '\n'; i++)
	{
		putchar(p_time[i]);
	}

	return 0;
}

int list_dir(char *dir_name)
{
	DIR *dirp;
	struct dirent *dp;
	struct stat buff;

	dirp = opendir(dir_name);
	chdir(dir_name);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] == '.')
		{
			continue;
		}

		if (lstat(dp->d_name, &buff) == -1)
		{
			perror(dir_name);
			exit(-1);
		}
		
		if (is_lnk(buff.st_mode))
		{
			list_file(buff);
			char buf[128];
			memset(buf,'\0',128);
			if((readlink(dp->d_name,buf,128))==-1)
			{
				perror("readlink");
				continue;
			}
			printf(" %s-> %s\n",dp->d_name,buf);
		}
		else
		{
			list_file(buff);
			printf(" %s\n", dp->d_name);
		}
	}

	closedir(dirp);
	return 0;
}

int main(int argc, char *argv[])
{
	struct stat buff;
	int i;


	if (argc < 2)
	{
		printf("loss argument!\n");
		return -1;
	}
	
	/*	argc >= 2	*/
	if (strcmp(argv[1], "-l") != 0)
	{
		printf("argument wrong!\n");
		return -1;
	}
	
	if (argc == 2)
	{	
		list_dir(".");
		return 0;
	}

	for (i = argc; i > 2; i--)
	{
		if(access(argv[i-1],F_OK)!=0)
		{
			printf("file %s no exit\n",argv[i-1]);
			continue;
		}
		if (lstat(argv[i - 1], &buff) == -1)
		{
			perror(argv[i - 1]);
			continue;
		}

		if (is_lnk(buff.st_mode))
		{
			list_file(buff);
			char buf[128];
			memset(buf,'\0',128);
			if((readlink(argv[i - 1],buf,128))==-1)	
			{
				perror("readlink");
				continue;
			}
			printf(" %s-> %s\n",argv[i-1],buf);
		}

		else if (is_dir(buff.st_mode))
		{
			list_dir(argv[i - 1]);
		}
		else
		{
			list_file(buff);
			printf(" %s", argv[i - 1]);
		}
		printf("\n");
	}
	return 0;
}

