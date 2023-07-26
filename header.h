#ifndef MAIN_H
#define MAIN_H

#define MYPROMT "0xissam$ "

#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

/**
 * struct data - holds the main data.
 * @av: Array of tokens to pass for execve
 * @cmd: The user input, the command line
 * @shname: The name of the shell program
 * @last_e_stat: last exit status of last command executed
 * @f_setenv: 1 if user did exec setenv (use it to free memory)
 */
typedef struct data
{
	char **av;
	char *cmd;
	const char *shname;
	int last_e_stat;
	int f_setenv;
} data;

/**
 * struct builtin - holds the main data.
 * @cmd: built in cmd
 * @f: function of builtin cmd
 */
typedef struct builtin
{
	const char *cmd;
	void (*f)(data *d);
} builtin;

/* executer.c */
void s_process(data *d);
void h_sigint(int sig);
void _exec(data *d);

/* path_handler.c */
char *_getenvirement(char *name);
int _locater(data *d);
int _setenv(data *d, char *name, char *value);

/* builtin_funcs.c */
int b_exec(data *d);
void b_exit(data *d);
void b_env(data *d);
void b_setenv(data *d);
void b_unsetenv(data *d);
void b_cd(data *d);

/* str_handler1.c */
unsigned int _strlenght(char *str);
int _strcompaire(const char *s1, const char *s2);
int _strncompaire(const char *s1, const char *s2, int n);
char *_strncpytodest(char *dest, const char *src);
char *_strappendtosrc(char *dest, const char *src);

/* str_handler2.c */
char *_strptl(const char *str);
int _isnum(const char *status);
int _isdigitalnum(int c);

/* helpe1.c */
void _prf(const char *str);
void f_array(char **array);
void spliter_func(data *d, const char *delim);
void init_d_func(data *d, const char *shname);
void r_cmd(data *d);

/* helpe2.c */
void p_stderr(const char *str1, const char *str2);
void trimer_func(char *str);
void *_realloc_mb(void *ptr, unsigned int new_size);


/* _getline.c */
#define R_B_S 1024

ssize_t _getline(char **lr, size_t *n, FILE *str_eam);


#endif
