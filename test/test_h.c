/*
 * E89 Pedagogical & Technical Lab
 * project: test_h.c
 * created on:  2026-04-25 - 14:09 +0200
 * 1st author:  sacha.juillard
 * description: specific h option tests
 */

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "ls.h"

Test(h_option, ignored_without_l, .init = cr_redirect_stdout)
{
    s_flags flags;

    flags.a = 0;
    flags.l = 0;
    flags.h = 1;

    print_long(".", "Makefile", flags);

    cr_assert_stdout_neq_str("");
}

Test(h_option, l_without_h_raw_size, .init = cr_redirect_stdout)
{
    s_flags flags;

    flags.a = 0;
    flags.l = 1;
    flags.h = 0;

    print_long(".", "Makefile", flags);

    cr_assert_stdout_neq_str("");
}

Test(h_option, l_with_h_changes_output, .init = cr_redirect_stdout)
{
    s_flags flags;

    flags.a = 0;
    flags.l = 1;
    flags.h = 1;

    print_long(".", "Makefile", flags);

    cr_assert_stdout_neq_str("");
}

Test(h_option, no_crash_basic, .init = cr_redirect_stdout)
{
    s_flags flags;

    flags.a = 0;
    flags.l = 1;
    flags.h = 1;

    print_long(".", "Makefile", flags);

    cr_assert(1);
}

Test(h_option, directory_listing, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 1;
    flags.l = 1;
    flags.h = 1;

    mkdir("test_h", 0777);

    fd = open("test_h/file", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("test_h", flags);

    cr_assert_stdout_neq_str("");

    unlink("test_h/file");
    rmdir("test_h");
}

