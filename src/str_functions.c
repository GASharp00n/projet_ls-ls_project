/*
 * E89 Pedagogical & Technical Lab
 * project:     str_functions.c
 * created on:  2026-03-31 - 12:10 +0200
 * 1st author:  sacha.juillard
 * description: string utility functions
 */

#include <unistd.h>
#include <stdlib.h>
#include "ls.h"

unsigned int stu_strlen(const char *str)
{
    unsigned int i;

    i = 0;
    while (str[i] != '\0') {
        i += 1;
    }
    return (i);
}

char *stu_strdup(char *src)
{
    char *copy;
    int i;
    int length;

    if (src == NULL) {
        return (NULL);
    }
    length = stu_strlen(src);
    copy = malloc(sizeof(char) * (length + 1));
    if (copy == NULL) {
        return (NULL);
    }
    i = 0;
    while (src[i] != '\0') {
        copy[i] = src[i];
        i += 1;
    }
    copy[i] = '\0';
    return (copy);
}

void putstr(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0') {
        write(1, &str[i], 1);
        i += 1;
    }
}

int stu_strcmp(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0'&& s2[i] != '\0' && s1[i] == s2[i]) {
        i += 1;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
