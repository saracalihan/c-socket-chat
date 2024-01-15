

#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "commons.h"
#include "user.h"


#define USAGE                                                                  \
  "C server example\n\t"                                                       \
  "/?: Help command\n\t"                                                        \
  "/c: connect command\n\t\t"                                                  \
  "example usage: /c username\n\t"                                              \
  "/b: Broadcast message\n\t\t"                                                 \
  "example usage: -Hello everyone\n\t"                                         \
  "/l: List online users\n\t"\
  "/q: Close connection\n\t"                                                    \
  "/h: Get message history\n"

typedef struct {
  char key;
  void (*func)(int serverfd, int clientfd, int threadId, char *buff);
  char usage[MAX_MESSAGE_LENGTH];
} Command;


void send_message_fn(int serverfd, int client, int thread, char *buf);
void list_user_fn(int serverfd, int client, int thread, char *buf);
void send_help_message_fn(int serverfd, int client, int thread, char *buf);
void send_broadcast_message_fn(int serverfd, int client, int thread, char *buf);
void close_connection_fn(int serverfd, int client, int thread, char *buf);
void send_history_message_fn(int serverfd, int client, int thread, char *buf);

static Command commands[] = {
  {
    .key = '?',
    .func = &send_help_message_fn,
    .usage = "[COMMAND] Help\n",
  },
  {
   .key = 'c',
    .func = &send_message_fn,
    .usage = "[COMMAND] Connect to user\n",
  },  {
   .key = 'b',
    .func = &send_broadcast_message_fn,
    .usage = "[COMMAND] Broadcast Message\n",
  },
  {
   .key = 'h',
    .func = &send_history_message_fn,
    .usage = "[COMMAND] History\n",
  },
  {
   .key = 'l',
    .func = &list_user_fn,
    .usage = "[COMMAND] List users\n",
  },
  {
   .key = 'q',
    .func = &close_connection_fn,
    .usage = "[COMMAND] Connection Close\n",
  }
};

#define COMMAND_COUNT (sizeof(commands) / sizeof(Command))

#endif // COMMANDS_H