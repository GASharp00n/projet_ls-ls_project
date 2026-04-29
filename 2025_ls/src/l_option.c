/*
 * E89 Pedagogical & Technical Lab
 * project:     l_option.c
 * created on:  2026-04-08 - 20:17 +0200
 * 1st author:  sacha.juillard
 * description: long format display (-l option)
 */

#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "ls.h"

void print_type(mode_t mode)
{
    if (S_ISREG(mode)) {
        write(1, "-", 1);
    } else if (S_ISDIR(mode)) {
        write(1, "d", 1);
    } else if (S_ISLNK(mode)) {
        write(1, "l", 1);
    } else if (S_ISCHR(mode)) {
        write(1, "c", 1);
    } else if (S_ISBLK(mode)) {
        write(1, "b", 1);
    } else if (S_ISSOCK(mode)) {
        write(1, "s", 1);
    } else {
        write(1, "?", 1);
    }
}

void print_permissions(mode_t mode)
{
    char p[9];

    p[0] = (mode & S_IRUSR) ? 'r' : '-';
    p[1] = (mode & S_IWUSR) ? 'w' : '-';
    p[2] = (mode & S_IXUSR) ? 'x' : '-';
    p[3] = (mode & S_IRGRP) ? 'r' : '-';
    p[4] = (mode & S_IWGRP) ? 'w' : '-';
    p[5] = (mode & S_IXGRP) ? 'x' : '-';
    p[6] = (mode & S_IROTH) ? 'r' : '-';
    p[7] = (mode & S_IWOTH) ? 'w' : '-';
    p[8] = (mode & S_IXOTH) ? 'x' : '-';
    write(1, p, 9);
}

void print_number(long n)
{
    char c;

    if (n >= 10) {
        print_number(n / 10);
    }
    c = '0' + (n % 10);
    write(1, &c, 1);
}

static void print_date(struct tm *tm)
{
    print_number(1900 + tm->tm_year);
    write(1, "-", 1);

    if (tm->tm_mon + 1 < 10) {
        write(1, "0", 1);
    }
    print_number(tm->tm_mon + 1);

    write(1, "-", 1);

    if (tm->tm_mday < 10) {
        write(1, "0", 1);
    }
    print_number(tm->tm_mday);
}

static void print_hour(struct tm *tm)
{
    write(1, " ", 1);

    if (tm->tm_hour < 10) {
        write(1, "0", 1);
    }
    print_number(tm->tm_hour);

    write(1, ":", 1);

    if (tm->tm_min < 10) {
        write(1, "0", 1);
    }
    print_number(tm->tm_min);
}

void print_time(time_t t)
{
    struct tm *tm;

    tm = localtime(&t);
    print_date(tm);
    print_hour(tm);
}

void build_path(char *dest, char *path, char *name)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (path[i]) {
        dest[i] = path[i];
        i += 1;
    }
    if (i > 0 && path[i - 1] != '/') {
        dest[i] = '/';
        i += 1;
    }
    while (name[j]) {
        dest[i + j] = name[j];
        j += 1;
    }
    dest[i + j] = '\0';
}

static void print_size_field(struct stat *st, s_flags flags)
{
    if (flags.h && flags.l) {
        print_human_size(st->st_size);
    } else {
        print_number(st->st_size);
    }
}

void print_long(char *path, char *name, s_flags flags)
{
    struct stat st;
    char full[1024];

    build_path(full, path, name);
    if (lstat(full, &st) == -1) {
        return;
    }
    print_type(st.st_mode);
    print_permissions(st.st_mode);
    write(1, " ", 1);
    print_number(st.st_nlink);
    write(1, " ", 1);
    print_number(st.st_uid);
    write(1, " ", 1);
    print_number(st.st_gid);
    write(1, " ", 1);
    print_size_field(&st, flags);
    write(1, " ", 1);
    print_time(st.st_mtime);
    write(1, " ", 1);
    putstr(name);
    write(1, "\n", 1);
}
