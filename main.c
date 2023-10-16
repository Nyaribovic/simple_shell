#include "shell.h"

/**
 * main - Entry point for the shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	/* Initializing the shell information */
	info_t info = INFO_INIT;
	int input_fd = STDIN_FILENO;

	if (argc == 2)
	{
		input_fd = open_input_file(argv[1]);
		if (input_fd == -1)
		{
			handle_open_file_error(argv[0], argv[1]);
			return (EXIT_FAILURE);
		}
		info.readfd = input_fd;
	}

	/* Initializing environment variables and read history */
	initialize_environment(&info);
	read_command_history(&info);

	/* Next, start the main shell loop */
	int exit_status = start_shell(&info, argv);

	return (exit_status);
}

/**
 * open_input_file - Open an input file and handle errors
 * @filename: Name of the input file
 *
 * Return: File descriptor or -1 on error
 */
int open_input_file(const char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
		{

			_write_string_stderr(filename);
			_write_string_stderr(": 0: Can't open ");
			_write_character_stderr(-1);
			_write_character_stderr('\n');
			exit(127);
		}
	}

	return (fd);
}

/**
 * initialize_environment - Initialize environment variables
 * @info: Pointer to info_t structure
 */
void initialize_environment(info_t *info)
{
	/* Populate environment variables list */
	populateEnvironmentList(info);
}

/**
 * start_shell - Start the shell's main loop
 * @info: Pointer to info_t structure
 * @argv: Argument vector
 *
 * Return: Exit status
 */
int start_shell(info_t *info, char **argv)
{
	/* Start the main shell loop */
	return (main_shell_loop(info, argv));
}

/**
 * main_shell_loop - Main shell loop logic
 * @info: Pointer to info_t structure
 * @argv: Argument vector
 *
 * Return: Exit status
 */
int main_shell_loop(info_t *info, char **argv)
{
	/* Main shell loop logic */
	/* We call the original hsh function code here */
	return (hsh(info, argv));
}

