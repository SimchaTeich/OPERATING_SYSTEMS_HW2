#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// https://stackoverflow.com/questions/3585846/color-text-in-terminal-applications-in-unix
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
int getCommandType(char **command);
void regularCommand(char **argv);
void directCommands(char *command[MAX_ARGS], int truncORAppend);

void parser(char *commands[MAX_COMMANDS][MAX_ARGS], char *stream);
void printCommands(char *commands[MAX_COMMANDS][MAX_ARGS]);
void executeCommands(char *commands[MAX_COMMANDS][MAX_ARGS]);
int numberOfArgs(char **command);

int main()
{
	char userInput[KB];
	char *commands[MAX_COMMANDS][MAX_ARGS] = {NULL};

	// ignoring the ^C
	signal(SIGINT, printCtrlCMsg);

	for (int j = 0; j < 100; j++)
	{
		// get commands from user
		printf(GRN "stshell" RESET "$ ");
		fgets(userInput, KB, stdin);
		userInput[strcspn(userInput, "\n")] = 0; // replace \n with \0

		// parsering the commands
		parser(commands, userInput);

		/* Is command empty */
		if (commands[0][0] == NULL)
		{
			continue;
		}

		/* Is exit the stshell*/
		if (strcmp(commands[0][0], "exit") == 0)
		{
			return 0;
		}

		switch (getCommandType(commands[0]))
		{
		case REGULAR:
			regularCommand(commands[0]);
			break;
		case DIRECT:
			directCommands(commands[0], O_TRUNC);
			break;
		case DOUBLE_DIRECT:
			directCommands(commands[0], O_APPEND);
			break;
		}
	}
}

void printCtrlCMsg()
{
	printf(RED "\nDo you want to kill me ha??\n" RESET);
}

int getCommandType(char **command)
{
	int argIndx = 0;
	while (argIndx < MAX_ARGS && command[argIndx] != NULL)
	{
		if (strcmp(command[argIndx], ">") == 0)
		{
			return DIRECT;
		}
		if (strcmp(command[argIndx], ">>") == 0)
		{
			return DOUBLE_DIRECT;
		}
		if (strcmp(command[argIndx], "|") == 0)
		{
			return;
		}
		argIndx++;
	}
	return REGULAR;
}

void pip_execp()
{

	int fd[2];
	if (pip(fd) < 0)
	{
		perror("Erorr");
		return 1;
	}

	int id_process = fork();
	if (id_process < 0)
	{
		perror("Erorr");
		return 1;
	}
	if (id_process == 0)
	{
		// first command
		close(fd[0]);
		int l = 0;
		// char *argv




	}
}

void regularCommand(char **argv)
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

void directCommands(char *command[MAX_ARGS], int truncORAppend)
{
	if (fork() == 0)
	{
		// make ^C be a valid option.
		signal(SIGINT, SIG_DFL);

		int argsNum = numberOfArgs(command);
		char *dstFileName = command[argsNum - 1];

		// remove the direct sign and the dst file name from list.
		command[argsNum - 1] = NULL;
		command[argsNum - 2] = NULL;

		// change the dst in fd
		int fileFD = open(dstFileName, O_WRONLY | O_CREAT | truncORAppend, S_IRUSR | S_IWUSR);
		close(STDOUT_FILENO);		 // close output
		dup2(fileFD, STDOUT_FILENO); // change output to be the file
		close(fileFD);				 // close the old place of dst file in fd

		execvp(command[0], command); // run the command
	}
	wait(NULL);
}

void parser(char *commands[MAX_COMMANDS][MAX_ARGS], char *stream)
{
	// divide to commands between the pipes (|)
	commands[0][0] = strtok(stream, "|");
	for (int i = 1; i < MAX_COMMANDS; i++)
	{
		commands[i][0] = strtok(NULL, "|");
	}

	// divide each command to parameters
	for (int i = 0; i < MAX_COMMANDS; i++)
	{
		commands[i][0] = strtok(commands[i][0], " ");
		for (int j = 1; j < MAX_ARGS; j++)
		{
			commands[i][j] = strtok(NULL, " ");
		}
	}
}

void printCommands(char *commands[MAX_COMMANDS][MAX_ARGS])
{
	for (int i = 0; i < MAX_COMMANDS; i++)
	{
		for (int j = 0; j < MAX_ARGS; j++)
		{
			printf("%s ", commands[i][j]);
		}
		printf("\n");
	}
}

void executeCommands(char *commands[MAX_COMMANDS][MAX_ARGS])
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

int numberOfArgs(char **command)
{
	int i = 0;
	for (; i < MAX_ARGS && command[i] != NULL; i++)
	{
	}

	return i;
}