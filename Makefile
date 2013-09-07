CC    = gcc
FLAGS = -pedantic -Wall -Wextra -std=c99 -o
FILES = cli.c misc.c cmd_mains.c arg_parse.c
EXEC  = cli

build : $(FILES)
	$(CC) $(FILES) $(FLAGS) $(EXEC) 

