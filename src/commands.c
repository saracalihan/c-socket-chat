#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void send_message_fn(int serverfd, int client, int thread, char *buf) {
  if (send(client, buf, 256, 0) == -1) {
    fprintf(stderr, "[THREAD-ERROR-%d] %m\n", thread);
    return;
  };

  printf("[SENDED-%d]: %s\n", thread, buf);
}

void send_help_message_fn(int serverfd, int client, int thread, char *buf) {
  send(client, USAGE, strlen(USAGE), 0);
}

void send_broadcast_message_fn(int serverfd, int client, int thread, char *buf){
  char m[] = "[INCOMING BROADCAST MESSAGE]: ";
  char *msg = malloc(sizeof(char) * MAX_MESSAGE_LENGTH);
  strcpy(msg,m);
  strcat(msg, buf);
  for (size_t i =0; i< threatCount; i++) {
      send(sockets[i],msg, strlen(msg),0);
  }
  printf("[BROADCAST-%d] %s\n", thread, &buf[1]);
}


void close_connection_fn(int serverfd, int client, int thread, char *buf){
  char msg[] = "Connection closing...\n";
  send(client, msg, strlen(msg), 0);
  close(client);
  avaibleListeners[thread] = true;
  sockets[thread] = -1;
  printf("[Thread-%d] Connection closed!\n", thread);
}


void send_history_message_fn(int serverfd, int client, int thread, char *buf){
  User user = users[thread];
  size_t stringSize = sizeof(char) * user.historyCount * MAX_MESSAGE_LENGTH;
  char* history = malloc(stringSize);
  memcpy(history, user.history, stringSize);
  send(client, history, stringSize, 0);
  free(history);
}
