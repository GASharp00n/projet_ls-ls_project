/*
 * E89 Pedagogical & Technical Lab
 * project: print_files.c
 * created on:  2026-04-08 - 20:19 +0200
 * 1st author:  sacha.juillard
 * description: file printer
 */

#include <unistd.h>
#include <stdlib.h>
#include "ls.h"

static void print_path_line(char *path, char *name, s_flags flags)
{
    if (flags.l)
        print_long(path, name, flags);
    else {
        putstr(name);
        write(1, "\n", 1);
    }
}

void print_files(char *path, char **files, int count, s_flags flags)
{
    int i;

    i = 0;
    while (i < count) {
        print_path_line(path, files[i], flags);
        free(files[i]);
        i += 1;
    }
    free(files);
}
