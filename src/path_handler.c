/*
 * E89 Pedagogical & Technical Lab
 * project: path_handler.c
 * created on:  2026-04-08 - 20:17 +0200
 * 1st author:  sacha.juillard
 * description: handle file or directory paths
 */

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "ls.h"

int is_directory(char *path)
{
    struct stat st;

    if (stat(path, &st) == -1) {
        return (0);
    }
    return (S_ISDIR(st.st_mode));
}

static void print_error(char *path)
{
    write(2, "./ls: ", 6);
    write(2, path, stu_strlen(path));
    write(2, ": ", 2);
    write(2, strerror(errno), stu_strlen(strerror(errno)));
    write(2, "\n", 1);
}

void handle_path(char *path, s_flags flags)
{
    struct stat st;

    if (stat(path, &st) == -1) {
        print_error(path);
        return;
    }
    if (S_ISDIR(st.st_mode)) {
        display_dir(path, flags);
        return;
    }
    if (flags.l) {
        print_long(".", path, flags);
    } else {
        putstr(path);
        write(1, "\n", 1);
    }
}
