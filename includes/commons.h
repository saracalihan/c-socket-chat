#ifndef _COMMON_H
#define _COMMON_H
#include <stdbool.h>


#define MAX_CONN 10
#define MAX_MESSAGE_LENGTH 156
#define MESSAGE_HISTORY_LENGTH 10
#define DEFAULT_MESSAGEBOX_CAPACITY 8

extern int sockets[MAX_CONN];
extern bool avaibleListeners[MAX_CONN];
extern unsigned int threatCount;

#endif // Common_h
