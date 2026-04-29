/*
 * E89 Pedagogical & Technical Lab
 * project:     sort_files.c
 * created on:  2026-03-31 - 12:01 +0200
 * 1st author:  sacha.juillard
 * description: function that sorts files using bubble sort
 */

#include "ls.h"

void sort_files(char **files, int count)
{
    int i;
    int j;
    int swapped;
    char *tmp;

    i = 0;
    while (i < count - 1) {
        swapped = 0;
        j = 0;
        while (j < count - i - 1) {
            if (stu_strcmp(files[j], files[j + 1]) > 0) {
                tmp = files[j];
                files[j] = files[j + 1];
                files[j + 1] = tmp;
                swapped = 1;
            }
            j += 1;
        }
        if (swapped == 0) {
            break;
        }
        i += 1;
    }
}
