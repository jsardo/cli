#ifndef CMD_MAINS_H
#define CMD_MAINS_H

int rm(const char *name, int vflag, int pflag, int rflag);
int rm_main(char *buf);
int ls(const char *name, int aflag, int iflag, int rflag);
int ls_main(char *buf);
int makedir(const char *name, int vflag);
int mkdir_main(char *buf);
int cat(const char *name, int nflag);
int cat_main(char *buf);
int cd(const char *name);
int cd_main(char *buf);
#endif
