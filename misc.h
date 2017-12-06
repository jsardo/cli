#ifndef MISC_H
#define MISC_H

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

#define NAME_MAX      100
#define BUFSIZE       1024
#define SCREEN_HEIGHT 25

int _argc;

int removedir(const char *name, int rflag);
char *strdup(const char *s);
int is_dir(const char *file);
int create_file(const char *name);
void error(char *fmt, ...);
int open_file(const char *name, int flag);
void usage(void);
int get_argc(char *s);
char **get_args(char *s, int index);
char *skip_flags(char *s);
char *get_flags(char *buf);
bool prompt(char *fmt, ...);

#endif
