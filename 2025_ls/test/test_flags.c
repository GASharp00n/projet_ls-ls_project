/*
 * E89 Pedagogical & Technical Lab
 * project: test_flags.c
 * created on:  2026-04-25 - 14:04 +0200
 * 1st author:  sacha.juillard
 * description: flag tests
 */

#include "ls.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

Test(flags, show_hidden, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 1;
    flags.l = 0;
    flags.h = 0;

    mkdir("hidden_dir", 0777);

    fd = open("hidden_dir/.secret", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("hidden_dir", flags);

    cr_assert_stdout_neq_str("");

    unlink("hidden_dir/.secret");
    rmdir("hidden_dir");
}

Test(flags, show_hidden_content, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 1;
    flags.l = 0;
    flags.h = 0;

    mkdir("ta", 0777);

    fd = open("ta/.hidden", O_CREAT | O_WRONLY, 0644);
    close(fd);

    fd = open("ta/visible", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("ta", flags);

    cr_assert_stdout_neq_str("");

    unlink("ta/.hidden");
    unlink("ta/visible");
    rmdir("ta");
}

Test(flags, hide_hidden_content, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 0;
    flags.l = 0;
    flags.h = 0;

    mkdir("ta2", 0777);

    fd = open("ta2/.hidden", O_CREAT | O_WRONLY, 0644);
    close(fd);

    fd = open("ta2/visible", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("ta2", flags);

    cr_assert_stdout_neq_str("");

    unlink("ta2/.hidden");
    unlink("ta2/visible");
    rmdir("ta2");
}

Test(flags, show_all_files, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 1;
    flags.l = 0;
    flags.h = 0;

    mkdir("adir", 0777);

    fd = open("adir/.hidden", O_CREAT | O_WRONLY, 0644);
    close(fd);

    fd = open("adir/visible", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("adir", flags);

    cr_assert(1);

    unlink("adir/.hidden");
    unlink("adir/visible");
    rmdir("adir");
}

Test(flags, hide_hidden_only_visible, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 0;
    flags.l = 0;
    flags.h = 0;

    mkdir("adir", 0777);

    fd = open("adir/.hidden", O_CREAT | O_WRONLY, 0644);
    close(fd);

    fd = open("adir/visible", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("adir", flags);

    cr_assert_stdout_neq_str("");

    unlink("adir/.hidden");
    unlink("adir/visible");
    rmdir("adir");
}
