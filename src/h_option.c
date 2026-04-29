/*
 * E89 Pedagogical & Technical Lab
 * project: h_option.c
 * created on:  2026-04-24
 * 1st author:  sacha.juillard
 * description: human readable size display (-h option)
 */

#include <unistd.h>
#include "ls.h"

void print_human_size(off_t size)
{
    const char *units = "KMGTPE";
    double s;
    int i;
    long int_part;
    long dec_part;

    s = (double) size;
    i = 0;
    while (s >= 1024 && units[i]) {
        s /= 1024;
        i += 1;
    }
    if (i == 0) {
        print_number((long) size);
        return;
    }
    int_part = (long) s;
    dec_part = (long) ((s - int_part) * 10);
    print_number(int_part);
    write(1, ".", 1);
    print_number(dec_part);
    write(1, &units[i - 1], 1);
}
