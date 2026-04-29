/*
 * E89 Pedagogical & Technical Lab
 * project: test_sort.c
 * created on:  2026-04-25 - 14:17 +0200
 * 1st author:  sacha.juillard
 * description: sort_files criterion  test
 */

#include <criterion/criterion.h>
#include "ls.h"

Test(sort_files, basic)
{
    char *files[] = {"z", "a", "m"};

    sort_files(files, 3);

    cr_assert_str_eq(files[0], "a");
    cr_assert_str_eq(files[1], "m");
    cr_assert_str_eq(files[2], "z");
}
