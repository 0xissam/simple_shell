#include "header.h"


/**
 * f_array - free arrayofpointers
 * @array: array of pointers
 * Return: nothing
 */
void f_array(char **array)
{
	int i;

	if (!array)
		return;

	for (i = 0; array[i]; i++)
	{
		free(array[i]);
		array[i] = NULL;
	}

	free(array);
}

/**
 * _prf - print a str to stdout
 * @str: str input
 * Return: nothing
 */
void _prf(const char *str)
{
	if (!str)
		return;
	while (*str)
	{
		write(STDOUT_FILENO, str, 1);
		str++;
	}
}

/**
 * r_cmd - get cmd from prompt and structure it
 * @d: data structinput
 * Return: nothing
 */
void r_cmd(data *d)
{
	size_t n = 0;
	ssize_t nread;
	int i = 0;

	nread = _getline(&d->cmd, &n, stdin);

	if (nread == -1)
	{
		free(d->cmd);
		exit(EXIT_SUCCESS);
	}

	d->cmd[nread - 1] = '\0';
	trimer_func(d->cmd);
	for (i = 0; d->cmd[i] != '\0'; i++)
	{
		if (d->cmd[0] == '#' || (d->cmd[i] == '#' && d->cmd[i - 1] == ' '))
		{
			d->cmd[i] = '\0';
			break;
		}
	}
	trimer_func(d->cmd);
}

/**
 * spliter_func - split string by a delimiter
 * @d: data structinput
 * @delim: str input
 * Return: nothing
 */
void spliter_func(data *d, const char *delim)
{
	char *token;
	int ntoken = 0;

	d->av = malloc(2 * sizeof(char *));
	if (d->av == NULL)
	{
		free(d->cmd);
		perror(d->shname);
		exit(EXIT_FAILURE);
	}
	d->av[0] = NULL;
	d->av[1] = NULL;

	token = strtok(d->cmd, delim);
	while (token)
	{
		d->av = realloc(d->av, (ntoken + 2) * sizeof(char *));
		if (d->av == NULL)
			goto free;
		d->av[ntoken] = _strptl(token);
		if (d->av[ntoken] == NULL)
			goto free;
		ntoken++;
		token = strtok(NULL, delim);
	}
	d->av[ntoken] = NULL;
	return;
free:
	f_array(d->av);
	free(d->cmd);
	perror(d->shname);
	exit(EXIT_FAILURE);
}

/**
 * init_d_func - init data
 * @d: data structinput
 * @shname: str input
 * Return: nothing
 */

void init_d_func(data *d, const char *shname)
{
	d->cmd = NULL;
	d->av = NULL;
	d->shname = shname;
	d->last_e_stat = EXIT_SUCCESS;
	d->f_setenv = 0;
}


