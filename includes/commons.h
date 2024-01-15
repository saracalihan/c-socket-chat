#ifndef _COMMON_H
#define _COMMON_H
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_CONN 10
#define MAX_MESSAGE_LENGTH 156
#define MESSAGE_HISTORY_LENGTH 10
#define DEFAULT_MESSAGEBOX_CAPACITY 8
#define BYTE_OF_MAX_MESSAGE (sizeof(char) * MAX_MESSAGE_LENGTH)

extern int sockets[MAX_CONN];
extern bool avaibleListeners[MAX_CONN];
extern unsigned int threatCount;

int fd_is_valid(int fd);

#endif // Common_h
