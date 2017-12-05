#include "misc.h"
#include "cmd_mains.h"
#include "arg_parse.h"

int rm_main(char *buf)
{
    char **args;
    int pflag = 0, vflag = 0, rflag = 0, hflag = 0, i = 0;

    args = get_args(buf, 2);
    char* flags = get_flags(buf);

    if (flags[0] != '\0') {
        do {
            switch (flags[i])
           {
                case 'v':
                   vflag = 1;
                   break;
                case 'p':
                   pflag = 1;
                   break;
                case 'r':
                   rflag = 1;
                   break;
                case 'h':
                   hflag = 1;
                   break;
           }
           i++;
        } while (flags[i] != '\0');
    }
    if (hflag) {
       printf("rm [FLAGS] [FILES(s)]\n"
               "remove the FILE(s)\n\n"
              "-p\tprompt before each removal\n"
              "-v\texplain what is being done\n"
              "-r\trecursively delete directories\n");
       return 1;
    }
    if (_argc == 0) {
        fprintf(stderr, "error: no operand.\n"
                        "Type 'rm -h' for more information.\n");
        return 1;
    }
    for (i = 0; i < _argc; ++i) {
        rm(args[i], vflag, pflag, rflag);
    }

    free_args(args);
    free_flags(flags);
    return 0;
}

int ls_main(char *buf)
{
    char **args;
    int aflag = 0, iflag = 0, rflag = 0, hflag = 0, i = 0;

    args = get_args(buf, 2);
    char* flags = get_flags(buf);

    if (flags[0] != '\0') {
        do {
            switch(flags[i])
            {
                case 'a':
                    aflag = 1;
                    break;
                case 'i':
                    iflag = 1;
                    break;
                case 'h':
                    hflag = 1;
                    break;
                case 'r':
                    rflag = 1;
                    break;
            }
            i++;
        } while (flags[i] != '\0');
    }

    if (hflag) {
ls_usage:
        printf("ls [FLAGS] [DIRECTORY]\n"
               "list the contents of DIRECTORY -- current dir is used if none given\n\n"
               "a\tdisplay hidden files (files starting with '.')\n"
               "i\tprint the index of each file\n"
               "r\trecursively list the contents of sub-directories\n");
        return 1;
    }
    if (_argc == 0)
        ls("./", aflag, iflag, rflag);
    else if (_argc > 1) {
        printf("ls: too many arguments\n\n");
        goto ls_usage;
    } else
        ls(args[0], aflag, iflag, rflag);

    free_args(args);
    free_flags(flags);
    return 0;
}

int mkdir_main(char *buf)
{
    char **args;
    int vflag = 0, hflag = 0, i = 0;

    args = get_args(buf, 5);
    char* flags = get_flags(buf);

   if (flags[0] != '\0') {
       do {
           switch (flags[i])
           {
               case 'h':
                   hflag = 1;
                   break;
               case 'v':
                   vflag = 1;
                   break;
           }
           i++;
       } while (flags[i] != '\0');
   }

   if (hflag) {
mkdir_usage:
       printf("mkdir [FLAGS] [DIRECTORY...]\n"
              "create a directory named DIRECTORY\n\n"
              "v\texplain what is being done\n");
       return 1;
   }
   if (_argc == 0) {
       printf("mkdir: no arguments given\n\n");
       goto mkdir_usage;
   } else {
       for (i = 0; i < _argc; ++i)
           makedir(args[i], vflag);
   }

   free_args(args);
   free_flags(flags);
   return 0;
}

int cat_main(char *buf)
{
    char **args;
    int nflag = 0, hflag = 0, i = 0;

    args = get_args(buf, 3);
    char* flags = get_flags(buf);

    if (flags[0] != '\0') {
        do {
            switch (flags[i])
            {
                case 'h':
                    hflag = 1;
                    break;
                case 'n':
                    nflag = 1;
                    break;
            }
            i++;
        } while (flags[i] != '\0');
    }

    if (hflag) {
cat_usage:
        printf("cat [FLAGS] [FILE]\n"
               "output the contents of FILE\n\n"
               "n\tnumber the lines of output\n");
        return 1;
    }
    if (_argc == 0) {
        printf("cat: no arguments given\n");
        goto cat_usage;
    } else if (_argc > 1) {
        printf("cat: too many arguments\n");
        goto cat_usage;
    } else
        cat(args[0], nflag);

    free_args(args);
    free_flags(flags);
    return 0;
}

int cd_main(char *buf)
{
    char **args;

    args = get_args(buf, 2);

    if (_argc == 0) {
        cd("/home");
        return 1;
    }
    else if (_argc > 1) {
        printf("cd: too many args.\n"
               "usage: cd DIRECTORY\n\n");
        return 1;
    }
    else
        cd(args[0]);

    free_args(args);
    return 0;
}