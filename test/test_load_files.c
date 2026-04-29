/*
 * E89 Pedagogical & Technical Lab
 * project: test_load_files.c
 * created on:  2026-04-25 - 14:16 +0200
 * 1st author:  sacha.juillard
 * description: load_files criterion tests
 */

#include "ls.h"
#include <criterion/criterion.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

Test(load_files, empty_dir)
{
    DIR *dir;
    char **files;
    int count;

    mkdir("empty_dir", 0777);

    dir = opendir("empty_dir");
    files = load_files(dir, &count, 0);
    closedir(dir);

    cr_assert_eq(count, 0);
    cr_assert_not_null(files);

    free(files);
    rmdir("empty_dir");
}

Test(load_files, includes_files)
{
    DIR *dir;
    char **files;
    int count;
    int found_a;
    int found_b;
    int i;
    int fd;

    mkdir("ldir", 0777);

    fd = open("ldir/a", O_CREAT | O_WRONLY, 0644);
    close(fd);

    fd = open("ldir/b", O_CREAT | O_WRONLY, 0644);
    close(fd);

    dir = opendir("ldir");
    files = load_files(dir, &count, 0);
    closedir(dir);

    found_a = 0;
    found_b = 0;

    i = 0;
    while (i < count)
    {
        if (files[i][0] == 'a')
            found_a = 1;
        if (files[i][0] == 'b')
            found_b = 1;
        free(files[i]);
        i += 1;
    }
    free(files);

    cr_assert(found_a == 1);
    cr_assert(found_b == 1);

    unlink("ldir/a");
    unlink("ldir/b");
    rmdir("ldir");
}
