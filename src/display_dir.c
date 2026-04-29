/*
 * E89 Pedagogical & Technical Lab
 * project: display_dir.c
 * created on:  2026-04-08 - 20:17 +0200
 * 1st author:  sacha.juillard
 * description: directory displayer
 */
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "ls.h"

void display_dir(char *path, s_flags flags)
{
    DIR *dir;
    char **files;
    int count;

    dir = opendir(path);
    if (dir == NULL) {
        putstr("./ls: ");
        putstr(path);
        putstr(": ");
        putstr(strerror(errno));
        write(2, "\n", 1);
        return;
    }
    files = load_files(dir, &count, flags.a);
    closedir(dir);
    if (files == NULL) {
        return;
    }
    if (count > 0) {
        sort_files(files, count);
    }
    print_files(path, files, count, flags);
}
