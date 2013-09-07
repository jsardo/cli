#include <dirent.h>
#include <getopt.h>
#include "misc.h"
#include "cmd_mains.h"

int rm(const char *name, int vflag, int pflag, int rflag) 
{
    if (pflag && !prompt("rm: remove \'%s\'? [y/n] ", name))
        return 0;
    
    if (is_dir(name) && rflag) {
        removedir(name, 1);
        return 0;
    }
    if (unlink(name) == -1) {
        error("can't delete file %s.", name);
    }
    if (vflag)
        printf("removed '%s'\n", name);
     
     return 0;
}

int ls(const char *name, int aflag, int iflag, int rflag)
{
    DIR *dp;
    struct dirent *ep;
    static int count = 0, index = 1;
    /* TODO: modify ouput to correctly align
     * contents when i and r flags are set */
    dp = opendir(name);
    if (dp != NULL) {
        while ((ep = readdir(dp)) != NULL) {
            if (!aflag && ep->d_name[0] == '.')
                continue;
            if (ep->d_type == 4 && rflag)
                ls(ep->d_name, aflag, iflag, rflag);
            (iflag) ? printf("%2d: %s", index++, ep->d_name) : printf("%10s", ep->d_name);
            if (count == 4) {
                putchar('\n');
                count = 0;
            } else {
                putchar('\t');
                count++;
            }
        }
        putchar('\n');
    } else {
        error("can't open directory %s.", name);
    }
    if (closedir(dp) == -1)
        error("can't close directory %s.", name);
   
    return 0;
}

int clear(void)
{
    int i;

    for (i = 0; i < SCREEN_HEIGHT; ++i)
        putchar('\n');
    return 0;
}

int makedir(const char *name, int vflag) 
{
    /* create dir with read/write priveleges */
    if (mkdir(name, S_IRWXU) == -1) 
        error("can't make directory %s.", name);
    if (vflag)
        printf("created directory '%s'\n", name);

    return 0;
}

int cat(const char *name, int nflag)
{
    int c;
    int count = 1;
    FILE *fp;

    if (is_dir(name)) { 
        fprintf(stderr, "error: '%s' is a directory\n", name);
        return 1;
    }
    fp = fopen(name, "r");
    if (fp == NULL) 
        error("can't open file %s.", name);
    
    if (nflag)
        printf("\t%d: ", count++);

    /* unbuffered input is used because it makes it easier to detect
     * newlines when the n flag is set. */
    while ((c = getc(fp)) != EOF) {
        putchar(c);
        if (c == '\n' && nflag)
            printf("\t%d: ", count++); 
    }
    if (c != '\n')
        putchar('\n');

    return 0;
}

int pwd(void)
{
    char buf[BUFSIZE];
    
    getcwd(buf, BUFSIZE);
    if (buf == NULL)
        error("can't get cwd.");
    puts(buf);

    return 0;
}

int cd(const char *path) 
{
    if (chdir(path) == -1)
        error("can't change to directory %s.", path);
    return 0;
}

int removedir(const char *name, int rflag)
{
    DIR *dp;
    struct dirent *ep;
    char cwd[NAME_MAX];

    if (rflag) {
        getcwd(cwd, NAME_MAX);
        dp = opendir(name);
        if (dp != NULL) {
            cd(name);
            while ((ep = readdir(dp)) != NULL) {
                /* deleting the '.' or ".." directory does not 
                * work so they are skipped.  Also. they don't 
                * have to be deleted for rmdir() to work */
                if (strcmp(ep->d_name, ".")  == 0 ||
                    strcmp(ep->d_name, "..") == 0)
                    continue;
                if (is_dir(ep->d_name))
                    removedir(ep->d_name, 1);
                else 
                    rm(ep->d_name, 0, 0, 0);
            }
        } else 
            error("can't open directory %s.", name);
        if (closedir(dp) == -1)
            error("can't close directory %s.", name);

        if (chdir(cwd) != -1) {
            if (rmdir(name) == -1) 
                error("can't delete directory %s.", name);
        } else 
            error("can't change to directory %s.", cwd);
    } else {
        if (rmdir(name) == -1)
            error("can't delete directory %s.", name);
    }

   return 0;
}

int main(void)
{
    char cwd[BUFSIZE], buf[BUFSIZE]; 

    do {
        getcwd(cwd, BUFSIZE);
        printf("cli:%s%% ", (cwd == NULL) ? "" : cwd);
        
        gets(buf);
        if (strlen(buf) == 0)   
            continue;
        if (strncmp(buf, "rm", 2) == 0 && !isalnum(buf[2]))
            rm_main(buf);
        else if (strncmp(buf, "ls ", 2) == 0 && !isalnum(buf[2]))
            ls_main(buf);
        else if (strncmp(buf, "clear", 5) == 0 && !isalnum(buf[5]))
            clear();
        else if (strncmp(buf, "mkdir", 5) == 0 && !isalnum(buf[5]))
            mkdir_main(buf);
        else if (strncmp(buf, "cat", 3) == 0 && !isalnum(buf[3]))
            cat_main(buf);
        else if (strncmp(buf, "pwd", 3) == 0 && !isalnum(buf[3]))
            pwd();
        else if (strncmp(buf, "cd", 2) == 0 && !isalnum(buf[2])) 
            cd_main(buf);
        else if (strncmp(buf, "help", 4) == 0 && !isalnum(buf[4]))
            usage();
        else
            printf("cli: not a valid command.\n"
                   "type 'help' for a list of options\n\n");
    } while (strcmp(buf, "exit") != 0);

    return 0;
} 
