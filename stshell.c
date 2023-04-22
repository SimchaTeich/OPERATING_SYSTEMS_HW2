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
void regularCommand(char** command);
void directCommands(char** command, int truncORAppend);
void parser(char* commands[MAX_COMMANDS][MAX_ARGS], char* stream);
void printCommands(char* commands[MAX_COMMANDS][MAX_ARGS]);
void executeCommands(char** command);
int numberOfArgs(char** command);
int numberOfCommands(char* commands[MAX_COMMANDS][MAX_ARGS]);
void handleThePipes(int fd_pipes[MAX_COMMANDS - 1][2], int numberOfCommands, int commandNo);


int main()
{
	char userInput[KB];
	char* commands[MAX_COMMANDS][MAX_ARGS] = {NULL};
	int fd_pipe[MAX_COMMANDS-1][2];
	int commandsAmount = 0;


	// ignoring the ^C
	signal(SIGINT, printCtrlCMsg);

	for(;;)
	{
		// get commands from user
	    printf(GRN "stshell" RESET "$ ");
	    fgets(userInput, KB, stdin);
	    userInput[strcspn(userInput, "\n")] = 0; // replace \n with \0

		// parsering the commands
		parser(commands, userInput);
		commandsAmount = numberOfCommands(commands);


	    /* Is command empty */ 
	    if (commands[0][0] == NULL){ continue; }

		/* Is exit the stshell*/
		if (strcmp(commands[0][0], "exit") == 0){ return 0; }

		
		pipe(fd_pipe[0]);
		pipe(fd_pipe[1]);
		for(int i = 0; i < commandsAmount; i++)//commands[i][0] != NULL; i++)
		{
			if(fork()==0)
			{
				// make ^C be a valid option.
				signal(SIGINT, SIG_DFL);
				
				/* prepare the pipes before running the commands */
				handleThePipes(fd_pipe, commandsAmount, i);

				/* run the current command */
				executeCommands(commands[i]);
			}
		}

		close(fd_pipe[0][1]);
		close(fd_pipe[0][0]);
		close(fd_pipe[1][1]);
		close(fd_pipe[1][0]);
		
		for(int i = 0; commands[i][0] != NULL; i++)
		{
			wait(NULL);
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


void regularCommand(char** command)
{
	// run the command
	execvp(command[0], command);
}


void directCommands(char** command, int truncORAppend)
{
	int argsNum = numberOfArgs(command);
	char* dstFileName = command[argsNum - 1];
	
	// remove the direct sign and the dst file name from list.
	command[argsNum - 1] = NULL;
	command[argsNum - 2] = NULL;
	
	//change the dst in fd
	int fileFD = open(dstFileName, O_WRONLY | O_CREAT | truncORAppend, S_IRUSR | S_IWUSR);
	close(STDOUT_FILENO);          // close output
	dup2(fileFD, STDOUT_FILENO);   // change output to be the file
	close(fileFD);                 // close the old place of dst file in fd

	execvp(command[0], command);   // run the command
}


/*
Parser string of commands and arguments/flags into
structre of 3d array.
For example: "ls -all | sort | grep txt"
will be [["ls", "-all"], ["sort"], ["grep", "txt"]]
input: pointer to 3d array and string of the full string.
output: void
*/
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


void executeCommands(char** command)
{
	switch(getCommandType(command))
	{
	case REGULAR:
		regularCommand(command);
		break;
	case DIRECT:
		directCommands(command, O_TRUNC);
		break;
	case DOUBLE_DIRECT:
		directCommands(command, O_APPEND);
		break;	
	}
}


int numberOfArgs(char** command)
{
	int i = 0;
	for(; i < MAX_ARGS && command[i] != NULL; i++){}

	return i;
}


int numberOfCommands(char* commands[MAX_COMMANDS][MAX_ARGS])
{
	int i = 0;
	for(; i < MAX_COMMANDS && commands[i][0] != NULL; i++);

	return i;
}


void handleThePipes(int fd_pipes[MAX_COMMANDS - 1][2], int numberOfCommands, int commandNo)
{
	if(commandNo == 0 && numberOfCommands > 1)
	{
		close(STDOUT_FILENO);
		dup2(fd_pipes[0][1], STDOUT_FILENO);
	}
	else if(commandNo == 1)
	{
		close(STDIN_FILENO);
		dup2(fd_pipes[0][0], STDIN_FILENO);

		if(numberOfCommands > 2)
		{
			close(STDOUT_FILENO);
			dup2(fd_pipes[1][1], STDOUT_FILENO);
		}
	}
	else if(commandNo == 2)
	{
		close(STDIN_FILENO);
		dup2(fd_pipes[1][0], STDIN_FILENO);
	}

	close(fd_pipes[0][1]);
	close(fd_pipes[0][0]);
	close(fd_pipes[1][1]);
	close(fd_pipes[1][0]);
}