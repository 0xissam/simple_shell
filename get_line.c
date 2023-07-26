#include "header.h"

/**
 * _getline_helper - getlinehelper func
 * @lr: str input
 * @n: int input
 * Return: int
 */
int _getline_helper(char **lr, size_t *n)
{
	if (*lr == NULL || *n == 0)
	{
		*n = 128;
		*lr = malloc(*n);
		if (*lr == NULL)
			return (-1);
	}
	return (0);
}

/**
 * _getline - reads input from FILE
 * @lr: str input
 * @n: int input
 * @str_eam: FILE input
 * Return: ssize_t
 */
ssize_t _getline(char **lr, size_t *n, FILE *str_eam)
{
	ssize_t byR = 0;
	size_t pos = 0, newS;
	static char buf[R_B_S];
	static size_t bufS, bufP;
	char *newB;

	if (lr == NULL || n == NULL || str_eam == NULL
		|| _getline_helper(lr, n) == -1)
		return (-1);
	while (1)
	{
		if (bufP >= bufS)
		{
			byR = read(str_eam->_fileno, buf, R_B_S);
			if (byR <= 0 && pos == 0)
				return (-1);
			else if (byR <= 0)
				break;
			bufS = byR;
			bufP = 0;
		}
		if (pos >= *n - 1)
		{
			newS = *n * 2;
			newB = realloc(*lr, newS);
			if (newB == NULL)
				return (-1);
			*lr = newB;
			*n = newS;
		}
		(*lr)[pos++] = buf[bufP++];
		if ((*lr)[pos - 1] == '\n')
			break;
	}
	(*lr)[pos] = '\0';
	return (pos);
}
