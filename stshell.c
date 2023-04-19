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

#define KB 1024
#define MAX_COMMANDS 3
#define MAX_ARGS 10
#define CRLF "\r\n"

void printCtrlCMsg();
int getCommandType(char** command);
void regularCommand(char** argv);
void directCommand(char* command);
void doubleDirectCommand(char* command);

void parser(char* commands[MAX_COMMANDS][MAX_ARGS], char* stream);
void printCommands(char* commands[MAX_COMMANDS][MAX_ARGS]);
void executeCommands(char* commands[MAX_COMMANDS][MAX_ARGS]);

int main()
{
	int i;
	char *argv[10];
	char command[1024];
	char saveCommand[1024];
	char *token;

	char userInput[KB];
	char* commands[MAX_COMMANDS][MAX_ARGS] = {NULL};

	// ignoring the ^C
	signal(SIGINT, printCtrlCMsg);

	for(int j = 0; j < 100; j++)
	{
		// get commands from user
	    printf(GRN "stshell$ " RESET);
	    fgets(userInput, KB, stdin);
	    userInput[strcspn(userInput, "\n")] = 0; // replace \n with \0

		// parsering the commands
		parser(commands, userInput);
		printCommands(commands);


	    /* Is command empty */ 
	    if (commands[0][0] == NULL){ continue; }

		/* Is exit the stshell*/
		if (strcmp(commands[0][0], "exit") == 0){ return 0; }


		switch(getCommandType(commands[0]))
		{
		case REGULAR:
			regularCommand(commands[0]);
			break;
		case DIRECT:
			//directCommand(saveCommand);
			break;
		case DOUBLE_DIRECT:
			//doubleDirectCommand(saveCommand);
			break;	
		}
	}
}


void printCtrlCMsg()
{
	printf(RED "\nDo you want to kill me ha??\n" RESET);
}


int getCommandType(char** command)
{
	int argIndx = 0;
	while(argIndx < MAX_ARGS && command[argIndx] != NULL)
	{
		if(strcmp(command[argIndx], ">") == 0)
		{
			return DIRECT;
		}
		if(strcmp(command[argIndx], ">>") == 0)
		{
			return DOUBLE_DIRECT;
		}
		argIndx++;
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


void parser(char* commands[MAX_COMMANDS][MAX_ARGS], char* stream)
{
	// divide to commands between the pipes (|)
	commands[0][0] = strtok(stream, "|");
	for(int i = 1; i < MAX_COMMANDS; i++)
	{
		commands[i][0] = strtok(NULL, "|");
	}

	// divide each command to parameters
	for(int i = 0; i < MAX_COMMANDS; i++)
	{
		commands[i][0] = strtok(commands[i][0], " ");
		for(int j = 1; j < MAX_ARGS; j++)
		{
			commands[i][j] = strtok(NULL, " ");
		}
	}
}


void printCommands(char* commands[MAX_COMMANDS][MAX_ARGS])
{
	for(int i = 0; i < MAX_COMMANDS; i++)
	{
		for(int j= 0; j < MAX_ARGS; j++)
		{
			printf("%s ", commands[i][j]);
		}
		printf("\n");
	}
}


void executeCommands(char* commands[MAX_COMMANDS][MAX_ARGS])
{
	// int i = 0;
	// char* filename;
	// int* dirrectMode = NULL; // updates to be O_TRUNC or O_APPEND

	// while(i < MAX_COMMANDS && commands[i][0] != NULL)
	// {
	// 	if(direct(commands[i], dirrectMode))
	// 	{

	// 	}

	// 	i++;
	// }	
}
