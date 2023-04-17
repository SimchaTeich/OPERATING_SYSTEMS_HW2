#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void printCtrlCMsg()
{
	printf("\nDo you want to kill me?? type \"exit\"..\n");
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
	    printf("hello: ");
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

			// waiting unitl commant will done.
			//wait(NULL);
	    } 
		wait(NULL); //   
	}
}
