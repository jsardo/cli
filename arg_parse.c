#include "arg_parse.h"

/* this file contains all of the argument parsing funtions that are used
 * to interpret the user input. */

int get_argc(char *s)
{
    char *sp = s;
    int count = 0;

    while (*sp != '\0') {
        while (isspace(*sp) && *sp != '\0')
            sp++;
        if (*sp == '\0')
            return count;
        else
            count++;
        while (!isspace(*sp) && *sp != '\0') 
            sp++;
    }
    return count;
}

char *skip_flag(char *s)
{
    while (!isspace(*s) && *s != '\0')
        s++;

    return s;
}

char **get_args(char *s, int index)
{
    char **args, arg[BUFSIZE], *argp;
    int i;
    args = (char **) malloc (BUFSIZE);

    s += index;
    _argc = get_argc(s);
    
    for (i = 0; i < _argc; i++) {
        argp = arg;
top: 
        while (isspace(*s))
            s++;
        if (*s == '-') {
            s = skip_flag(s);
            _argc--;
            goto top;
        }
        while (!isspace(*s) && *s != '\0')
            *argp++ = *s++;

        *argp = '\0';
        args[i] = strdup(arg);
    }
    
    return args;
}

char *get_flags(char *buf, char *flags)
{
    while (*buf != '\0') {
        if (*buf == '-') {
            buf++;
            while (!isspace(*buf) && *buf != '\0')
                *flags++ = *buf++;
        }
        buf++;
    }
    *flags = '\0';
    return flags;
}

void free_args(char **args) {
    for (int i = 0; i < _argc; i++) {
        free(args[i]);
    }
    free(args);
}

void free_flags(char *flags) {
    free(flags);
}