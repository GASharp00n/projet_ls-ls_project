/*
 * E89 Pedagogical & Technical Lab
 * project: test_directory.c
 * created on:  2026-04-25 - 13:40 +0200
 * 1st author:  sacha.juillard
 * description: criterion tests for directory related functions
 */

#include "ls.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

Test(display_dir, prints_files, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 0;
    flags.l = 0;
    flags.h = 0;

    mkdir("testdir", 0777);

    fd = open("testdir/a", O_CREAT | O_WRONLY, 0644);
    close(fd);

    fd = open("testdir/b", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("testdir", flags);

    cr_assert_stdout_neq_str("");

    unlink("testdir/a");
    unlink("testdir/b");
    rmdir("testdir");
}

Test(path, file_only, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 0;
    flags.l = 0;
    flags.h = 0;

    fd = open("file.txt", O_CREAT | O_WRONLY, 0644);
    close(fd);

    handle_path("file.txt", flags);

    cr_assert_stdout_neq_str("");

    unlink("file.txt");
}
