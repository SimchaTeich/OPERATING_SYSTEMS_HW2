#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
#define GRN "\x1B[32m"
#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void printCtrlCMsg()
{
	printf(RED "\nDo you want to kill me ha??\n" RESET);
}


int main()
{
	int i;
	char *argv[10];
	char command[1024];
	char *token;

	// ignoring the ^C
	signal(SIGINT, printCtrlCMsg);//SIG_IGN);

	for(int j = 0; j < 100; j++)
	{
	    printf(GRN "stshell$ " RESET);
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

	    /* parse command line */
	    i = 0;
	    token = strtok (command," ");
	    while (token != NULL)
	    {
			argv[i] = token;
			token = strtok (NULL, " ");
			i++;
	    }
	    argv[i] = NULL;

	    /* Is command empty */ 
	    if (argv[0] == NULL){ continue; }

		if (strcmp(argv[0], "exit") == 0){ return 0; }

	    /* for commands not part of the shell command language */ 
	    if (fork() == 0)
		{
			// mkae ^C be a valid option.
			signal(SIGINT, SIG_DFL);
			
			// run the command
			execvp(argv[0], argv);
	    } 
		wait(NULL);   
	}
}
