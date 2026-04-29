/*
 * E89 Pedagogical & Technical Lab
 * project: test_l_option.c
 * created on:  2026-04-25 - 14:16 +0200
 * 1st author:  sacha.juillard
 * description: l_option specific criterion tests
 */

#include "ls.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

Test(l_option, basic_file, .init = cr_redirect_stdout)
{
    s_flags flags;
    int fd;

    flags.a = 0;
    flags.l = 1;
    flags.h = 0;

    mkdir("lt", 0777);

    fd = open("lt/file", O_CREAT | O_WRONLY, 0644);
    close(fd);

    display_dir("lt", flags);

    cr_assert_stdout_neq_str("");

    unlink("lt/file");
    rmdir("lt");
}
