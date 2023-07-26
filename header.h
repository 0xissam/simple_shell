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
 * struct builtin - data.
 * @cmd: builtin cmd
 * @f: builtin cmd func
 */
typedef struct builtin
{
	const char *cmd;
	void (*f)(data *d);
} builtin;

/**
 * struct data - data agrs.
 * @av: list of tokens for exec
 * @cmd: the cmd line
 * @shname: shell name
 * @last_e_stat: last exit last cmd executed
 * @f_setenv: 1 if exec setenv
 */
typedef struct data
{
	char **av;
	char *cmd;
	const char *shname;
	int last_e_stat;
	int f_setenv;
} data;


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

/* first_handler1.c */
void _prf(const char *str);
void f_array(char **array);
void spliter_func(data *d, const char *delim);
void init_d_func(data *d, const char *shname);
void r_cmd(data *d);

/* second_handler.c */
void p_stderr(const char *str1, const char *str2);
void trimer_func(char *str);
void *_realloc_mb(void *ptr, unsigned int new_size);


/* _getline.c */
#define R_B_S 1024

ssize_t _getline(char **lr, size_t *n, FILE *str_eam);


#endif
