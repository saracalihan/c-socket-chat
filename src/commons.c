#include "commons.h"

int sockets[MAX_CONN]; // Gerçek tanımlama
bool avaibleListeners[MAX_CONN]; // Gerçek tanımlama
unsigned int threatCount = 0; // Gerçek tanımlama
User users[MAX_CONN] = {0}; // Gerçek tanımlama
