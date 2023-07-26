#include "header.h"

/**
 * main - main func
 * @argc: @argv size
 * @argv: array of cmdline args
 * Return: 0.
 */
int main(int argc, char **argv)
{
	data d;
	(void)argc;
	init_d_func(&d, argv[0]);
	_exec(&d);

	return (0);
}
