#ifndef NETWORK
#define NETWORK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL_net.h>

#include "board.h"


#define MAX_PENDING_CONNECTIONS 3 // Server only

#define SERVER_IP "127.0.0.1" //Client will get this from an input box

#define PORT 6969
#define MAX_BUFFER_SIZE 1024



int server(board_t* board);

int client(board_t* board);




#endif