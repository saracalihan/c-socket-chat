

#ifndef COMMANDS_H
#define COMMANDS_H
#include "commons.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define USAGE                                                                  \
  "C server example\n\t"                                                       \
  "/?: Help command\n\t"                                                        \
  "/c: connect command\n\t\t"                                                  \
  "example usage: /c username\n\t"                                              \
  "/b: Broadcast message\n\t\t"                                                 \
  "example usage: -Hello everyone\n\t"                                         \
  "/q: Close connection\n\t"                                                    \
  "/h: Get message history\n"

typedef struct {
  char key;
  void (*func)(int serverfd, int clientfd, int threadId, char *buff);
  char usage[MAX_MESSAGE_LENGTH];
} Command;


void send_message_fn(int serverfd, int client, int thread, char *buf);
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
   .key = 'q',
    .func = &close_connection_fn,
    .usage = "[COMMAND] Connection Close\n",
  }
};

#define COMMAND_COUNT (sizeof(commands) / sizeof(Command))

#endif // COMMANDS_H