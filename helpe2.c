#include "header.h"


/**
 * _realloc_mb - reallocates a memory block
 *
 * @ptr: void pointer
 * @new_size: unsigned intiger
 *
 * Return: newly allocat mem
 */
void *_realloc_mb(void *ptr, unsigned int new_size)
{
	char *p;
	unsigned int i, tp = new_size, old_size = sizeof(ptr);

	if (old_size == new_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size > old_size)
		tp = old_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	p = malloc(new_size);

	for (i = 0; i < tp; i++)
		p[i] = ((char *)ptr)[i];
	free(ptr);
	return (p);
}



/**
 * trimer_func - rm leading,trailing,spaces,tabs from str
 * @str: str input
 * Return: nothing.
 */

void trimer_func(char *str)
{
	int i, j, len = _strlenght(str);

	for (i = 0; i < len && (str[i] == ' ' || str[i] == '\t'); i++)
		;

	for (j = 0; i < len ; i++, j++)
		str[j] = str[i];

	str[j] = '\0';

	for (i = _strlenght(str) - 1; i > 0 && (str[i] == ' ' || str[i] == '\t'); i--)
		str[i] = '\0';
}

/**
 * p_stderr - print stderr
 * @str1: shell progra name
 * @str2: msg error
 * Return: nothing
 */
void p_stderr(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return;

	while (*str1)
	{
		write(STDERR_FILENO, str1, 1);
		str1++;
	}

	write(STDERR_FILENO, ": ", 2);

	while (*str2)
	{
		write(STDERR_FILENO, str2, 1);
		str2++;
	}
	write(STDERR_FILENO, "\n", 1);
}
