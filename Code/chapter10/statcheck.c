#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc,char **argv)
{
	struct stat stat;

	char *type,*readok;

	Stat(argv[1],&stat); //包裹函数

	if(S_ISREG(stat.st_mode))
		type = "reg";
	else if(S_ISDIR(stat.st_mode))
		type = "dir";
	else 
		type = "other";

	if(stat.st_mode & S_IRUSR)
		readok = "yes";
	else
		readok = "no";

	printf("type:%s,read: %s\n",type,readok);

	return 0;
}
