#include "exec.h"

/* rempli paths avec les différents chemins possibles pour exec */
void makePaths(char ***paths, char *exec)
{
	/* c'est un peu comme makeCmd */
}

void execute(char **newArgv)
{
	pid = fork();
	switch(pid)
	{
		case -1 :
			printf("Erreur de forkation\n");
			exit(EXIT_FAILURE);
			break;
		case 0 :
			int i = 0;
			char **paths;
			do
			{
				res = execv(newArgv[0], newArgv);
				newArgv[0] = paths[i];
				i++;
			}while(res == -1);
			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		default :
			waitpid(pid, NULL, 0);
			break;
	}
}