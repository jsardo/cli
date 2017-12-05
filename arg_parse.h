#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include "misc.h"

int get_argc(char *s);
char *skip_flag(char *s);
char **get_args(char *s, int index);
void free_args(char **args);
char *get_flags(char *buf, char *flags);
void free_flags(char *flags);
#endif
