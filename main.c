#include <stdlib.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "cmds.h"
#include "exec.h"

int main(int argc, char **argv, char *envp[])
{
	char buffer[BUF_SIZE];
	FILE *hist;
	setEnvironnement();
	if(!makeCmdsPath(argv[0]))
	{
		exit(EXIT_FAILURE);
	}
	hist = fopen(cmdsPath[HISTORY],"a+");
	if(hist == NULL)
	{
		fprintf(stderr, "%s\n", strerror(errno));
	}
	printPrefix();
	while(fgets(buffer, BUF_SIZE, stdin) != NULL)
	{
		if(buffer[0]!='\n')
		{
			setPipe(hist, buffer);
		}
		printPrefix();
	}
	printf("\n");
	return 0;
}	
