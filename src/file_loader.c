/*
 * E89 Pedagogical & Technical Lab
 * project: file_loader.c
 * created on:  2026-04-08 - 20:18 +0200
 * 1st author:  sacha.juillard
 * description: loads files from directory
 */

#include <dirent.h>
#include <stdlib.h>
#include "ls.h"

static void free_files(char **files, int count)
{
    int i;

    i = 0;
    while (i < count) {
        free(files[i]);
        i += 1;
    }
    free(files);
}

static char **resize_array(char **files, int count, int new_cap)
{
    char **new_files;
    int i;

    new_files = malloc(sizeof(char *) * (new_cap + 1));
    if (new_files == NULL) {
        return (NULL);
    }
    i = 0;
    while (i < count) {
        new_files[i] = files[i];
        i += 1;
    }
    free(files);
    return (new_files);
}

static char **add_file(char **files, int *count, int *capacity, char *name)
{
    char **tmp;

    if (*count >= *capacity)
    {
        tmp = resize_array(files, *count, *capacity * 2);
        if (!tmp)
            return NULL;
        files = tmp;
        *capacity *= 2;
    }

    files[*count] = stu_strdup(name);
    if (!files[*count])
        return NULL;

    (*count) += 1;
    return files;
}

char **load_files(DIR *dir, int *count, int show_all)
{
    struct dirent *entry;
    char **files;
    char **tmp;
    int capacity;

    capacity = 10;
    *count = 0;
    files = malloc(sizeof(char *) * (capacity + 1));
    if (!files)
        return NULL;

    entry = readdir(dir);
    while (entry) {
        if (show_all || entry->d_name[0] != '.') {
            tmp = add_file(files, count, &capacity, entry->d_name);
            if (!tmp) {
                free_files(files, *count);
                return NULL;
            }
            files = tmp;
        }
        entry = readdir(dir);
    }

    files[*count] = NULL;
    return files;
}
