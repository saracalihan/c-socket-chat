#include "commands.h"
#include "commons.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdbool.h>

void send_message_fn(int serverfd, int client, int thread, char *buf) {
  char *name = &buf[3];
  char* msg = malloc(BYTE_OF_MAX_MESSAGE);
  memset(msg, 0, BYTE_OF_MAX_MESSAGE);

  // Find to wanted user
  User* from = &users[thread], *to=0;
  for (size_t i=0; i< threatCount; i++) {
    int isExist =strcmp(users[i].name, name);

    // Last user
    if(isExist !=0 && i+1 == threatCount){
      sprintf(msg, "User not found: '%s'\n", name);
      send(client, msg, strlen(msg), 0);
      free(msg);
      return;
    }else if(isExist !=0) {
      continue;
    }
    to = &users[i];
    break;
  }

  // Connection request
  char waitMsg[] = "[INFO] Connection request sended. Waiting to accept...\n";
  send(from->socket, waitMsg, strlen(waitMsg),0);

  sprintf(msg, "[MESSAGE REQUEST] %s want to send message. Accept to connect? [y/n]:", from->name);
  send(to->socket, msg, strlen(msg), 0);
  memset(msg, 0, BYTE_OF_MAX_MESSAGE);
  recv(to->socket, msg, 2,0);

  // Accept answer check
  if (strcmp(msg, "y") !=0 || strcmp(msg, "n") !=0 ) {
    bool isWrongAgain = false;
    do {
      sprintf(msg, "\n[MESSAGE REQUEST] Invalid answer '%s'. Accept to connect? [y/n]:", msg);
      send(to->socket, msg, strlen(msg), 0);
      memset(msg, 0, BYTE_OF_MAX_MESSAGE);
      recv(to->socket, msg, 2,0);
      isWrongAgain = strcmp(msg, "y") !=0 || strcmp(msg, "n") !=0;
    }while (isWrongAgain);
  }

  // Reciver decline connection
  if(strcmp(msg, "n") ==0 ){
    sprintf(msg, "\n[MESSAGE REQUEST] Reciver decline to connection request\n", msg);
    send(from->socket, msg, strlen(msg), 0);
    free(msg);
    return;
  }

  // TODO: Create duplex message line
  // TODO: Recive and send message
  //         - Add message to user.messageBox.sendedMessages | user.messageBox.incameMessages
  //         - Increase user.messageBox.messageCount's
  // TODO: Create special message commands like /M? (Message ?, message help, message commands list), /MH (Message History), /MQ (Message Quit, close message connection)

  printf("[THREAD-%d] %d -> %d connection created\n");
}

void list_user_fn(int serverfd, int client, int thread, char *buf){
  char* u = malloc(BYTE_OF_MAX_MESSAGE);
  memset(u, 0, BYTE_OF_MAX_MESSAGE);
  strcat(u, "Online users: \n");
  for(size_t i = 0;i< threatCount; i++){
    if(avaibleListeners[i] == false){
      sprintf(u,"%s\t- %s\n", u, users[i].name);
    }
  }
  send(client, u,strlen(u),0);
  free(u);
}

void send_help_message_fn(int serverfd, int client, int thread, char *buf) {
  send(client, USAGE, strlen(USAGE), 0);
}

void send_broadcast_message_fn(int serverfd, int client, int thread, char *buf){
  char *msg = malloc(BYTE_OF_MAX_MESSAGE);

  // Skip "/b " part.
  buf = &buf[3];
  sprintf(msg, "[BROADCAST MESSAGE FROM %s]: %s\n", users[thread].name, buf);

  // Send message to all users
  for (size_t i =0; i< threatCount; i++) {
      send(sockets[i], msg, strlen(msg), 0);
  }
  printf("[BROADCAST-%d] %s\n", thread, buf);
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
