#include "header.h"

/**
 * b_cd - cd
 * @d: data structinput
 * Return: nothing
 */
void b_cd(data *d)
{
	char *dir = d->av[1];
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	_setenv(d, "PWD", cwd);
	if (!dir)
		dir = _getenvirement("HOME");
	if (chdir(dir) == -1)
		perror("cd");
	else
	{
		_setenv(d, "OLDPWD", _getenvirement("PWD"));
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd() error");
		_setenv(d, "PWD", cwd);
	}
}
