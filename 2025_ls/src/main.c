/*
 * E89 Pedagogical & Technical Lab
 * project:     main.c
 * created on:  2026-03-31 - 12:15 +0100
 * 1st author:  sacha.juillard
 * description: main program for ls
 */

#include <unistd.h>
#include "ls.h"

static void init_flags(s_flags *flags)
{
    flags->a = 0;
    flags->l = 0;
    flags->h = 0;
}

static void parse_option_char(char c, s_flags *flags)
{
    if (c == 'a') {
        flags->a = 1;
    } else if (c == 'l') {
        flags->l = 1;
    } else if (c == 'h') {
        flags->h = 1;
    }
}

static void parse_options(int argc, char **argv, s_flags *flags)
{
    int i;
    int j;

    i = 1;
    while (i < argc) {
        if (argv[i][0] == '-') {
            j = 1;
            while (argv[i][j] != '\0') {
                parse_option_char(argv[i][j], flags);
                j += 1;
            }
        }
        i += 1;
    }
}

static int count_paths(int argc, char **argv)
{
    int i;
    int count;

    i = 1;
    count = 0;
    while (i < argc) {
        if (argv[i][0] != '-') {
            count += 1;
        }
        i += 1;
    }
    return count;
}

static void print_header(char *path, int multiple)
{
    if (multiple) {
        putstr(path);
        write(1, ":\n", 2);
    }
}

static int handle_arguments(int argc, char **argv, s_flags flags)
{
    int i;
    int handled;
    int multiple;

    i = 1;
    handled = 0;
    multiple = (count_paths(argc, argv) > 1);

    while (i < argc) {
        if (argv[i][0] != '-') {
            if (handled && multiple) {
                write(1, "\n", 1);
            }
            print_header(argv[i], multiple);
            handle_path(argv[i], flags);
            handled = 1;
        }
        i += 1;
    }
    return handled;
}

int main(int argc, char **argv)
{
    s_flags flags;
    int handled;

    init_flags(&flags);
    parse_options(argc, argv, &flags);
    handled = handle_arguments(argc, argv, flags);

    if (argc == 1 || !handled) {
        display_dir(".", flags);
    }
    return 0;
}
