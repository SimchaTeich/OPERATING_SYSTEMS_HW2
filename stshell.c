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

#define REGULAR 0
#define DIRECT 1
#define DOUBLE_DIRECT 2

void printCtrlCMsg();
int getCommandType(char** argv, int items);
void regularCommand(char** argv);
void directCommand(char* command);
void doubleDirectCommand(char* command);

int main()
{
	int i;
	char *argv[10];
	char command[1024];
	char saveCommand[1024];
	char *token;

	// ignoring the ^C
	signal(SIGINT, printCtrlCMsg);//SIG_IGN);

	for(int j = 0; j < 100; j++)
	{
	    printf(GRN "stshell$ " RESET);
	    fgets(command, 1024, stdin);
	    command[strlen(command) - 1] = '\0'; // replace \n with \0

		// save the command
		strcpy(saveCommand, command);

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

		/* Is exit the stshell*/
		if (strcmp(argv[0], "exit") == 0){ return 0; }


		switch(getCommandType(argv, i))
		{
		case REGULAR:
			regularCommand(argv);
			break;
		case DIRECT:
			directCommand(saveCommand);
			break;
		case DOUBLE_DIRECT:
			doubleDirectCommand(saveCommand);
			break;	
		}
	}
}


void printCtrlCMsg()
{
	printf(RED "\nDo you want to kill me ha??\n" RESET);
}


int getCommandType(char** argv, int items)
{
	for(int i = 0; i < items; i++)
	{
		if(strcmp(argv[i], ">") == 0)
		{
			return DIRECT;
		}
		if(strcmp(argv[i], ">>") == 0)
		{
			return DOUBLE_DIRECT;
		}
	}
	return REGULAR;
}


void regularCommand(char** argv)
{
	if (fork() == 0)
	{
		// make ^C be a valid option.
		signal(SIGINT, SIG_DFL);
		
		// run the command
		execvp(argv[0], argv);
	} 
	wait(NULL);
}


void directCommand(char* command)
{
	if (fork() == 0)
	{
		// make ^C be a valid option.
		signal(SIGINT, SIG_DFL);

		char saveCommand[1024];
		char* cmdName;
		char* cmdArgs[10];
		char* dst;
		int i = 0;

		// save the command
		strcpy(saveCommand, command);
		
		cmdName = strtok(saveCommand, ">");
		dst = strtok(NULL, ">");
		cmdName[strlen(cmdName) - 1] = '\0';
		strcpy(dst, &dst[1]);

		cmdArgs[i] = strtok(cmdName, " ");
		while(cmdArgs[i] != NULL)
		{
			cmdArgs[++i] = strtok(NULL, " ");
		}
		
		//change the dst in fd
		int fileFD = open(dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		close(STDOUT_FILENO);      // close output
		dup2(fileFD, STDOUT_FILENO);   // change output to be the file
		close(fileFD); // close the old place of dst file in fd

		// run the command
		execvp(cmdArgs[0], cmdArgs);
		//close(1);
	} 
	wait(NULL);
}


void doubleDirectCommand(char* command)
{
	if (fork() == 0)
	{
		// make ^C be a valid option.
		signal(SIGINT, SIG_DFL);

		char saveCommand[1024];
		char* cmdName;
		char* cmdArgs[10];
		char* dst;
		int i = 0;

		// save the command
		strcpy(saveCommand, command);
		
		cmdName = strtok(saveCommand, ">>");
		dst = strtok(NULL, "?>");
		cmdName[strlen(cmdName) - 1] = '\0';
		strcpy(dst, &dst[1]);

		cmdArgs[i] = strtok(cmdName, " ");
		while(cmdArgs[i] != NULL)
		{
			cmdArgs[++i] = strtok(NULL, " ");
		}
		
		//change the dst in fd
		//change the dst in fd
		int fileFD = open(dst, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
		close(STDOUT_FILENO);      // close output
		dup2(fileFD, STDOUT_FILENO);   // change output to be the file
		close(fileFD); // close the old place of dst file in fd

		// run the command
		execvp(cmdArgs[0], cmdArgs);
		
		// close the file
		//close(fileFD);
	} 
	wait(NULL);
}