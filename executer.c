#include "header.h"

/**
 * h_sigint - signal handler_func
 * @signal: int input
 * Return: nothing
 */

void h_sigint(int signal)
{
	(void)signal;
	exit(EXIT_FAILURE);
}

/**
 * s_process - start new process
 * @d: data structinput
 * Return: nothing
 */

void s_process(data *d)
{
	pid_t c_pid = fork();
	int status = 0;

	if (c_pid == -1)
		goto free;
	if (c_pid == 0 && execve(d->av[0], d->av, NULL) == -1)
		goto free;
	else if (wait(&status) == -1)
		goto free;
	if (WIFEXITED(status))
		d->last_e_stat = WEXITSTATUS(status);
	return;
free:
	perror(d->shname);
	f_array(d->av);
	free(d->cmd);
	exit(EXIT_FAILURE);
}


/**
 * _exec - exectute command
 * @d: data structinput
 * Return: nothing
 */

void _exec(data *d)
{
	const char prompt[] = MYPROMT;

	signal(SIGINT, h_sigint);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			_prf(prompt);

		r_cmd(d);
		if (_strlenght(d->cmd) != 0)
		{
			spliter_func(d, " ");
			if (!b_exec(d))
			{
				_locater(d);
				if (access(d->av[0], F_OK) == -1)
				{
					perror(d->shname);
				}
				else
				{
					s_process(d);
				}
			}
			f_array(d->av);
		}
		free(d->cmd);
	}
}
