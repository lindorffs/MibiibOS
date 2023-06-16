#ifndef UTILS_H
#define UTILS_H

#include <mibstd.h>

d_u_int strlen(const char*);
int streq(const char *, const char *);
void strsplit(const char *, char *, d_u_int);
u_int ctoi(const char);
void itos(char *str, int i);
void itoa(d_u_int, char[5]);

#endif
