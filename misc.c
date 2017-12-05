#include "misc.h"

void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, " "); 
    perror(NULL);
    va_end(args);
    exit(1);
}
    
bool prompt(char *fmt, ...) 
{
    char c;
    va_list args;
    
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    
    c = getchar();
    if (c == 'y')
        return true; 
    else
        return false;
}

void usage(void)
{
    printf("cli usage: COMMAND [FLAGS] ([FILE(s)])\n\n"
           "rm\tdelete a file.\n"
           "ls\tlist directory contents.\n"
           "mkdir\tcreat a directory.\n"
           "cat\tprint contents of a file.\n"
           "cd\tchange working directory.\n\n"
           "appending \" -h\" to most commands will give\n"
           "additional info regarding that command\n\n");
}

char *strdup(const char *s)
{
    char *d = malloc(strlen(s) + 1);
    if (d == NULL)
        return NULL;
    strcpy(d, s);
    return d; 
}

int is_dir(const char *file)
{
    struct stat statbuf;
    
    stat(file, &statbuf);
    return S_ISDIR(statbuf.st_mode);
}

int create_file(const char *name)
{
    int fd;
    if ((fd = creat(name, S_IRWXU)) == -1)
        error("can't create file %s.", name);
    return fd;
}

int open_file(const char *name, int flag)
{
    int fd;

    fd = open(name, flag);
    if (fd == -1)
        error("can't open file %s.", name);
    return fd;
}
