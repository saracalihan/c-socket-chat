#include "commons.h"
#include <string.h>

int sockets[MAX_CONN]; // Gerçek tanımlama
bool avaibleListeners[MAX_CONN]; // Gerçek tanımlama
unsigned int threatCount = 0; // Gerçek tanımlama


int fd_is_valid(int fd){
    return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

void new_line_to_null(char* str){
    char* c = strchr(str, '\n');
    if (c == NULL) {
        str[strlen(str) -1] = '\0';
    } else {
        *c = '\0';
    }
}
