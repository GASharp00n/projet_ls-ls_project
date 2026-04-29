/*
 * E89 Pedagogical & Technical Lab
 * project: test_utils.c
 * created on:  2026-04-25 - 14:17 +0200
 * 1st author:  sacha.juillard
 * description: multiple utilities criterion tests
 */

#include "ls.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(putstr, basic, .init = cr_redirect_stdout)
{
    putstr("hello");
    cr_assert_stdout_eq_str("hello");
}

Test(putstr, newline, .init = cr_redirect_stdout)
{
    putstr("\n");
    cr_assert_stdout_eq_str("\n");
}

Test(stu_strlen, normal)
{
    cr_assert_eq(stu_strlen("hello"), 5);
}

Test(stu_strlen, empty)
{
    cr_assert_eq(stu_strlen(""), 0);
}

Test(stu_strcmp, equal)
{
    cr_assert_eq(stu_strcmp("abc", "abc"), 0);
}

Test(stu_strcmp, order)
{
    cr_assert(stu_strcmp("a", "b") < 0);
}

Test(stu_strcmp, reverse)
{
    cr_assert(stu_strcmp("b", "a") > 0);
}

Test(stu_strcmp, prefix)
{
    cr_assert(stu_strcmp("abc", "ab") > 0);
}

Test(stu_strdup, normal)
{
    char *copy;

    copy = stu_strdup("hello");
    cr_assert_not_null(copy);
    cr_assert_str_eq(copy, "hello");
    free(copy);
}

Test(stu_strdup, null_input)
{
    char *copy;

    copy = stu_strdup(NULL);
    cr_assert_null(copy);
}
