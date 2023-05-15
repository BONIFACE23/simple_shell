#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
/**
 * main- function
 * Return:0
 **/
void display_prompt(void);
void remove_newline(char *str);
void execute_command(char *command);

int main(void)
{
	char input[BUFFER_SIZE];

	while (1)
	{
		display_prompt();

		if (fgets(input, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		remove_newline(input);
		execute_command(input);
	}

	return (0);
}
/**
 * display_prompt - prompt
 * Return:void
 **/

void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * remove_newline - remove
 * @str:string
 * Return:0
 **/
void remove_newline(char *str)
{
	size_t length = strlen(str);

	if (str[length - 1] == '\n')
	{
		str[length - 1] = '\0';
	}
}
/**
 * execute_command - command
 * @command:to be executed
 * Return:void
 **/
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execlp(command, command, (char *)NULL) == -1)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		int status;

		waitpid(pid, &status, 0);

		if (status != 0)
		{
			printf("Command not found: %s\n", command);
		}
	}
}

