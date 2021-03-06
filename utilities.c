#include "utilities.h"


void makePaths(char **paths, char *exec, char ***finalPaths, int nbPaths)
{
	int i;
	*finalPaths = malloc(sizeof(char *)*nbPaths);
	for(i=0;i<nbPaths;i++)
	{
		(*finalPaths)[i] = malloc(sizeof(char)*(strlen(paths[0])+strlen(exec)+1));
		strcpy((*finalPaths)[i], paths[i]);
		strcat((*finalPaths)[i], "/");
		strcat((*finalPaths)[i], exec);
	}
}

int parser(char *buffer, char ***elem, char sep)
{
	int i=0, endElem=0, startElem=0, nbElems=0, numElem = 0;
	while(buffer[i] != '\n' && buffer[i] != '\0')
	{
		if(buffer[i] == sep)
		{
			while(buffer[i] == sep)
			{
				i++;
			}
		}
		else
		{
			nbElems++;
			while(buffer[i] != sep && buffer[i] != '\n' && buffer[i] != '\0')
			{
				i++;
			}
		}
	}
	*elem = malloc(sizeof(char *)*(nbElems+1));
	i=0;
	do
	{
		if(buffer[i] == sep)
		{
			if(buffer[i-1] == '\\') // Si le séparateur est échappé
			{
				strcpy(&(buffer[i-1]), &(buffer[i]));
			}
			else
			{
				while(buffer[i] == sep)
				{
					i++;
				}
			}
		}
		else
		{
			startElem = i;
			while(buffer[i] != sep && buffer[i] != '\n' && buffer[i] != '\0')
			{
				i++;
			}
			endElem = i;
			(*elem)[numElem] = malloc(sizeof(char)*endElem-startElem);
			strncpy((*elem)[numElem], &(buffer[startElem]), endElem-startElem);
			(*elem)[numElem][endElem-startElem] = '\0';
			numElem++;
		}
	}while(buffer[i] != '\n' && buffer[i] != '\0');
	(*elem)[numElem] = NULL;
	return nbElems;
}

void setEnvironnement()
{
	char *tmp;
	struct utsname machine;
	
	if(getenv("LOGNAME") == NULL)
	{
		setenv(getlogin(), "LOGNAME", 0);
	}
	if(getenv("HOME") == NULL)
	{
		tmp = malloc(sizeof(char)*(strlen("/home/")+strlen(getenv("LOGNAME")+1)));
		strcpy(tmp, "/home/");
		strcat(tmp, getenv("LOGNAME"));
		setenv(tmp, "HOME", 0);
		free(tmp);
	}
	if(getenv("PWD") == NULL)
	{
		tmp = getcwd(NULL, 0);
		setenv("PWD", tmp, 1);
		free(tmp);
	}
	if(getenv("HOSTNAME") == NULL)
	{
		uname(&machine);
		setenv("HOSTNAME", machine.nodename, 1);
	}
}

void replaceTilde(char **args)
{
	char *temp;
	int i;
	for(i=0;args[i] != NULL;i++)
	{
		if((args[i])[0] == '~')
		{
			temp = malloc(sizeof(char)*(strlen(getenv("HOME"))+strlen(args[i])));
			strcpy(temp, getenv("HOME"));
			strcat(temp, &(args[i][1]));
			free(args[i]);
			args[i] = temp;
		}
	}
}

/*
 * Affichage de l'invite de commande
 */
void printPrefix()
{
	if(strncmp(getenv("PWD"), getenv("HOME"), strlen(getenv("HOME"))) == 0)
	{
		printf("%s@%s:~%s >> ", getenv("LOGNAME"), getenv("HOSTNAME"), getenv("PWD")+strlen(getenv("HOME")));
	}
	else
	{
		printf("%s@%s:%s >> ", getenv("LOGNAME"), getenv("HOSTNAME"), getenv("PWD"));
	}
}
