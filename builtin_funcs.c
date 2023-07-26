#include "header.h"

/**
 * b_exec - checkif builtin and exec
 * @d: data structinput
 * Return: 1 for builtin, or 0 for not
 */
int b_exec(data *d)
{
	builtin builtin[] = {
		{"exit", b_exit},
		{"env", b_env},
		{"setenv", b_setenv},
		{"unsetenv", b_unsetenv},
		{"cd", b_cd},
		{NULL, NULL},
	};
	int k = 0;

	for (k = 0; builtin[k].cmd; k++)
	{
		if (_strcompaire(d->av[0], builtin[k].cmd) == 0)
		{
			builtin[k].f(d);
			return (1);
		}
	}
	return (0);
}


/**
 * b_env - print current env
 * @d: data structinput
 * Return: nothing
 */
void b_env(data *d)
{
	int c = 0;

	(void)d;
	while (environ[c])
	{
		_prf(environ[c]);
		_prf("\n");
		c++;
	}
}
/**
 * b_setenv - init new env var,
 * or modify existing
 * @d: data structinput
 * Return: nothing
 */

void b_setenv(data *d)
{
	(void)d;
	if (d->av[1] && d->av[2])
	{
		if (_setenv(d, d->av[1], d->av[2]) == -1)
		{
			perror("setenv");
		}
	}
}

/**
 * b_unsetenv - remove env var
 * @d: data structinput
 * Return: nothing
 */
void b_unsetenv(data *d)
{
	int i, j;
	int len;

	(void)d;
	if (!d->av[1] || !getenv(d->av[1]))
	{
		p_stderr(d->shname, "variable not found.");
		return;
	}
	len = strlen(d->av[1]);
	for (i = 0; environ[i]; i++)
		if (strncmp(environ[i], d->av[1], len) == 0 && environ[i][len] == '=')
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
}


/**
 * b_exit - exit sh shell
 * @d: data structinput
 * Return: nothing
 */
void b_exit(data *d)
{
	const char *errS = "./hsh: 1: exit: Illegal number: ";

	if (d->av[1])
	{
		if (d->av[1][0] != '-' && _isnum(d->av[1]))
			d->last_e_stat = atoi(d->av[1]);
		else
		{
			write(STDERR_FILENO, errS, strlen(errS));
			write(STDERR_FILENO, d->av[1], strlen(d->av[1]));
			write(STDERR_FILENO, "\n", 1);
			d->last_e_stat = 2;
		}
	}
	f_array(d->av);
	free(d->cmd);
	if (d->f_setenv)
		f_array(environ);
	exit(d->last_e_stat);
}