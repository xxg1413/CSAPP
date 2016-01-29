#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	int fd1, fd2;

	fd1 = open("../footbar.txt", O_RDONLY, 0);
	fd2 = open("../foo.txt", O_RDONLY, 0);

	close(fd2);

	fd2 = open("../baz.txt",O_RDONLY,0);

	printf("fd2 = %d\n", fd2); //

	exit(0);

}