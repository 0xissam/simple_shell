#include "header.h"

/**
 * _isdigitalnum - check if char is num
 * @c: char
 * Return: 1 ifor digit or 0
 */
int _isdigitalnum(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * _strptl - pointer newly allocated space in mem,
 * contains copy of the str given as a param.
 *
 * @str: str input
 *
 * Return: pointer
 */
char *_strptl(const char *str)
{
	int i, len = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;

	result = (char *)malloc((len + 1) * sizeof(char));

	if (result == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		result[i] = str[i];

	return (result);
}

/**
 * _isnum - check if str is a num
 * @status: str check
 * Return: nothing
 */
int _isnum(const char *status)
{
	if (status == NULL || status[0] == '\0')
		return (0);
	while (*status)
	{
		if (!_isdigitalnum(*status))
			return (0);
		status++;
	}
	return (1);
}
