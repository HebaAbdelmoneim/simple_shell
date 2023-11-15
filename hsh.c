#include "shell.h"

/**
 * main - Entry point
 * @argc: number of argc
 * @argv: array of arg strings
 * @envp: array of envp variables strings
 *
 * Return: Always 0
 */

int main(int __attribute__((unused)) argc, char *argv[], char *envp[])
{
	while (1)
	{
		char **cmd = malloc(BUFFER_SIZE * sizeof(char *));
		char **args = malloc(BUFFER_SIZE * sizeof(char *));
		char *command = NULL, *dir = NULL, cm1[100] = "/bin/";
		unsigned int entry = 1;
		size_t len = 1024;

		/*entry = command_start_message("$", entry);*/
		if (getline(&command, &len, stdin) == -1)
		{
			free(dir), free(cmd);
			free(command), free(args);
			exit(100);
		}
		command[_strcspn(command, "\n")] = '\0';
		if (_strlen(command) == 0)
			continue;
		else
			cmd = get_tokens(command);
		dir = strtok(cmd[0], "/");
		dir = strtok(NULL, "/");
		args[0] = dir, args[1] = cmd[1];
		args[2] = cmd[2], args[3] = NULL;
		strcat(cm1, dir);
		if (is_builtin_command(cmd[0]))
		{
			if (_strcmp(args[0], "exit") == 0)
				break;
			else if (_strcmp(args[0], "cd") == 0)
				handle_cd(args[1], envp);
		}
		else if (access(cm1, X_OK) == -1)
			handle_error(argv[0], entry, dir, strerror(errno));
		else
			get_process(envp, cm1, args);
		 free(dir), free(cmd);
		 free(args), free(command);
	}
	return (0);
}
