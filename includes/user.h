#ifndef _USER_H
#define _USER_H
#include "dynamicarray.h"
#include "commons.h"

typedef struct {
  int to;
  char *incomingMessages;
  unsigned int incameMessagesCount;
  char *sendedMessages;
  unsigned int sendedMessagesCount;
} Messages;

CreateDynamicArray(Messages);
// CreateDynamicArrayFunctions(Messages);

typedef struct {
  int socket;
  char *history; // 10*256 char
  unsigned int historyCount;
  char *name;
  DA_Messages messageBox;
} User;

extern User users[MAX_CONN];

#endif