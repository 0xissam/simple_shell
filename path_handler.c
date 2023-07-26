#include "header.h"

/**
 * _getenvirement - val of env var.
 * @name: str input
 * Return: val env var
 */

char *_getenvirement(char *name)
{
	int i = -1;
	size_t name_len;

	if (name == NULL || *name == '\0')
		return (NULL);
	if (environ == NULL)
		return (NULL);

	name_len = _strlenght(name);

	while (environ[++i])
	{
		if (!_strncompaire(environ[i], name, name_len) && environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
	}
	return (NULL);
}

/**
 * _locater - locate exc file associatedwith a given cmd.
 * @d: str input
 * Return: nothing
 */
int _locater(data *d)
{
	char *token, *path,
		*paths = malloc(_strlenght(_getenvirement("PATH") ? _getenvirement("PATH") : "") + 1);
	size_t token_len;
	int find = -1;

	if (!_getenvirement("PATH"))
		goto step_out;
	_strncpytodest(paths, _getenvirement("PATH"));
	if (paths == NULL)
		goto step_out;
	token = strtok(paths, ":");
	while (token)
	{
		token_len = _strlenght(token) + _strlenght(d->av[0]) + 2;
		path = malloc(token_len);
		if (path == NULL)
			return (find);
		_strncpytodest(path, token);
		_strappendtosrc(path, "/");
		_strappendtosrc(path, d->av[0]);
		if (access(path, F_OK) == 0)
		{
			free(d->av[0]);
			d->av[0] = _strptl(path);
			free(path);
			find = 0;
			break;
		}
		free(path);
		token = strtok(NULL, ":");
	}
step_out:
	free(paths);
	return (find);
}

/**
 * create_new_entry - init a new env var,
 *  or modify existing
 * @name: var name
 * @value: var value
 * Return: nothing
 */
char *create_new_entry(char *name, char *value)
{
	size_t new_len = strlen(name) + strlen(value) + 2;
	char *new_entry = malloc(new_len);

	if (new_entry == NULL)
		return (NULL);

	strcpy(new_entry, name);
	strcat(new_entry, "=");
	strcat(new_entry, value);

	return (new_entry);
}


/**
 * _new_environ - init a new env var,
 *  or modify existing
 * @name: var name
 * @value: var value
 * Return: nothing
 */
char **_new_environ(char *name, char *value)
{
	int env_len = 0, i = 0;
	char *new_entry;
	char **new_environ;

	while (environ[env_len])
		env_len++;
	new_entry = create_new_entry(name, value);
	if (new_entry == NULL)
		return (NULL);
	new_environ = _getenvirement(name) ? malloc((env_len + 1) * sizeof(char *))
								: malloc((env_len + 2) * sizeof(char *));

	if (!new_environ)
	{
		free(new_entry);
		return (NULL);
	}
	for (i = 0; environ[i]; i++)
	{
		new_environ[i] = malloc(strlen(environ[i]) + 1);
		if (!new_environ[i])
		{
			f_array(new_environ);
			free(new_entry);
			return (NULL);
		}
		if (strncmp(environ[i], name, strlen(name)) == 0
		&& environ[i][strlen(name)] == '=')
			strcpy(new_environ[i], new_entry);
		else
			strcpy(new_environ[i], environ[i]);
	}
	if (!_getenvirement(name))
	{
		new_environ[env_len] = new_entry;
		new_environ[env_len + 1] = NULL;
	}
	else
		new_environ[env_len] = NULL;
	return (new_environ);
}

/**
 * _setenv - init a new env var,
 *  or modify existing
 * @d: to flag
 * @name: var name
 * @value: var value
 * Return: nothing
 */
int _setenv(data *d, char *name, char *value)
{
	char **new_environ;

	if (!name || !value)
		return (-1);

	new_environ = _new_environ(name, value);
	if (!new_environ)
		return (-1);
	environ = new_environ;
	d->f_setenv = 1;

	return (0);
}