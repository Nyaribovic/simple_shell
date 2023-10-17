#include "shell.h"
#include <string.h>

void print_error(info_t *info, const char *estr);

/**
 * exitShell - Exits the shell.
 * @info: Structure containing potential arguments.
 *
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit".
 */
int exitShell(info_t *info)
{
	int exitCheck;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitCheck = _atoi(info->argv[1]);
		if (exitCheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			string_print(info->argv[1]);
			character_print('\n');
			return (1);
		}
		info->err_num = _atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * changeDirectory - Changes the current directory of the process.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int changeDirectory(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		string_print("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = getEnvironmentValue(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = getEnvironmentValue(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getEnvironmentValue(info, "OLDPWD="))
		{
			string_print(s);
			character_print('\n');
			return (1);
		}
		string_print(getEnvironmentValue(info, "OLDPWD="));
		character_print('\n');
		chdir_ret = chdir((dir = getEnvironmentValue(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		string_print(info->argv[1]);
		character_print('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", getEnvironmentValue(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * helpCommand - Displays a help message.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int helpCommand(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	string_print("help call works. Function not yet implemented\n");
	if (0)
		string_print(*arg_array); /* temp att_unused workaround */
	return (0);
}
