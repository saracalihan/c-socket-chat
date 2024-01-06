#include <assert.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <pthread.h>
#include <stdbool.h>
#include <signal.h>

#include "commons.h"
#include "commands.h"

#define PORT 3000
int socketfd = -1;
bool startListenders = false;

void print_error(char* message){
    fprintf(stderr, "[ERROR] %s: %m", message);
    free(message);
    abort();
};

void close_connections(int){
    startListenders = false;
    printf("socker: %d\n", socketfd);
    printf("[INFO] Server closing...\n");
    for (size_t i=0; i<threatCount; i++) {
        close(sockets[i]);
        printf("[INFO] Socket %d closed %i\n", i, sockets[i]);
    }
    if(socketfd != -1){
        close(socketfd);
        printf("[INFO] Server socket closed\n");
    }
    exit(0);
}

int bind_socket(int socket, struct sockaddr_in* address){
    return bind(socketfd, address, sizeof(*address));
}

void* listen_inet(void*args){
    int id = ((int*)args)[0],
        client = ((int*)args)[1];
    avaibleListeners[id] = false;
    sockets[id] = client;
    
    User* user = &(users[id]);
    user->socket = client;
    user->messages = malloc(sizeof(char) *MAX_MESSAGE_LENGTH*MESSAGE_HISTORY_LENGTH);
    // memset(user->messages, 0, sizeof(char) * MAX_MESSAGE_LENGTH*MESSAGE_HISTORY_LENGTH);
    printf("id: %d\n", id);
    user->message_count =0;
    printf("[THREAD-%d] Thread initialized to %i\n", id, client );
    while (!startListenders) {
        printf("[THREAD-%d] wait to start\n", id);
    }
    printf("[THREAD-%d] Start to listening\n", id);
    bool isConnectedToUser= false;
    while (avaibleListeners[id] == false  && sockets[id] != -1) {
        char buf[MAX_MESSAGE_LENGTH] = {0};
        recv(client, buf, MAX_MESSAGE_LENGTH, 0);
        printf("[RECIVED-%d]: %s\n",id, buf);


        strcpy(&user->messages[user->message_count*MAX_MESSAGE_LENGTH], buf);
        user->message_count++;

        if(isConnectedToUser){
            //mesaj işlemleri
            continue;
        }

        if(buf[0] !='/'){
            char errorMsg[] ="[ERROR] Wrong command: ";
            strcat(errorMsg, buf);
            send(client, errorMsg, strlen(errorMsg) , 0);
            send_help_message_fn(socketfd, client, id, buf);
            continue;
        }

        for (size_t i=0; i<COMMAND_COUNT; i++) {
            Command c = commands[i];
            if( c.key != buf[1] ){
                if(i +1 != COMMAND_COUNT){
                    continue;
                }

                char errorMsg[] = "[ERROR] Unknown command: ";
                strcat(errorMsg, buf);
                send(client, errorMsg, strlen(errorMsg),0);

                break;
            }

            send(client, c.usage, strlen(c.usage), 0);
            c.func(socketfd, client, id, buf);
            break;
        }

    }

}

int main()
{

    int port = PORT;
    if (signal(SIGINT, &close_connections) == SIG_ERR || signal(SIGQUIT, &close_connections) == SIG_ERR || signal(SIGQUIT, &close_connections) == SIG_ERR)
        printf("\ncan't catch SIG\n");

    memset(&sockets, -1, sizeof(sockets));
    memset(&avaibleListeners, 0, sizeof(avaibleListeners));

    pthread_t threads[MAX_CONN] = {0};

    printf("Pid: %d\n", getpid());
    socketfd = socket( AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
        print_error("socket");
    }
    printf("[INFO] Socket created\n");

    struct sockaddr_in address = {
        AF_INET,
        htons(port),
        0
    };

    // SOCKET BINDING
    if(bind_socket(socketfd, &address) == -1){

        // If port is already in use try next port
        while (1) {
            port++;
            printf("[INFO] Bind error: %m\n");
            printf("[INFO] Trying to bind %d\n", port);
            address.sin_port=       htons(port);
            if(bind_socket(socketfd, &address) != -1){
                break;
            }
        }
    }
    printf("[INFO] Bound to %d\n", port);

    if(listen(socketfd, MAX_CONN)==-1){
        close(socketfd);
        print_error("listen");
    }

    printf("[INFO] Listening to %d\n", port);
    startListenders = true;

    while (startListenders) {
        int client = accept(socketfd, 0, 0);
        if(client == -1){
            print_error("accept");
        }
        printf("[INFO] Client accepted! %i\n",client );

        int args[2] = {threatCount, client};
        pthread_create(&threads[threatCount], NULL, &listen_inet, (void*)args);
        threatCount++;
    }
    return EXIT_SUCCESS;
}
