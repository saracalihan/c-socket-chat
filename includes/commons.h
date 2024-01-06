#ifndef COMMON_H
#define COMMON_H
#include <stdbool.h>

#define MAX_CONN 10
#define MAX_MESSAGE_LENGTH 156
#define MESSAGE_HISTORY_LENGTH 10

typedef struct {
  int socket;
  char *messages; // 10*256 char
  unsigned int message_count;
  char *name;
} User;

extern int sockets[MAX_CONN];
extern bool avaibleListeners[MAX_CONN];
extern unsigned int threatCount;
extern User users[MAX_CONN];

#endif // Common_h
