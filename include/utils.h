#ifndef UTILS_H
#define UTILS_H

#include <mibstd.h>

d_u_int strlen(const char*);
int streq(const char *, const char *);
void strsplit(const char *, char *, char *, char);
u_int ctoi(const char);
void itos(char *str, int i);
char* itoa(q_u_int, char*);

#endif
