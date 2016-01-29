#include "csapp.h"

int main()
{
	int n;
	rio_t rio;
	char buf[MAXLINE];

	rio_readinitb(&rio, STDIN_FILENO);

	whle((n= rio_readn(&rio, buf, MAXBUF)) != 0)
		Rio_writen(STDOUT_FILENO, buf, MAXBUF);

	return 0;
}