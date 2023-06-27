#ifndef OS_H_
#define OS_H_

#include <mibstd.h>

#define OS_MAJOR 2
#define OS_MINOR 1
#define OS_V 2 
#define OS_VERSION "Dragur"

typedef struct OSInfo {
	char *hostname;
	char *username;
	char *password;
} OSInfo;

u_int os_auth(void);

void os_entry(void);
void os_print(const char *);
void os_prtuser(void);
void os_prthost(void);
void os_lock(void);
void os_init(void);

char *os_get_user(void);

#endif
