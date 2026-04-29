/*
 * E89 Pedagogical & Technical Lab
 * project:     mini_ls.h
 * created on:  2026-03-31 - 12:10 +0200
 * 1st author:  sacha.juillard
 * description: header for ls functions
 */
#ifndef LS_H_
#define LS_H_

#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

typedef struct s_flags {
    int a;
    int l;
    int h;
} s_flags;

void putstr(char *str);
int stu_strcmp(const char *s1, const char *s2);
void sort_files(char **files, int count);
char *stu_strdup(char *src);
unsigned int stu_strlen(const char *str);
int is_directory(char *path);
void display_dir(char *path, s_flags flags);
void handle_path(char *path, s_flags flags);
void print_files(char *path, char **files, int count, s_flags flags);
char **load_files(DIR *dir, int *count, int show_all);
void print_long(char *path, char *name, s_flags flags);
void print_type(mode_t mode);
void print_permissions(mode_t mode);
void print_number(long n);
void print_time(time_t t);
void print_human_size(off_t size);
void build_path(char *dest, char *path, char *name);
#endif
