#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include "misc.h"

int get_argc(char *s);
char *skip_flag(char *s);
char **get_args(char *s, int index);
char *get_flags(char *buf);
void free_args(char **args);
void free_flags(char *flags);
#endif
