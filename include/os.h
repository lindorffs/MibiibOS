#ifndef OS_H_
#define OS_H_

#include <mibstd.h>

#define OS_VERSION "1.0.5"

void os_entry();
void os_print(char *);

char *os_get_user(void);

#endif
