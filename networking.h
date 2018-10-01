#ifndef CLIENT_H_
#define CLIENT_H_

#include <SDL2/SDL_net.h>

#define RECV_MAX_LEN 1024

extern TCPsocket sock;
extern const char *server_addr;
extern const int server_port;

// initial connection to the game server
void connect_to_server();

// disconnect from game server
void disconnect_from_server();

// send a JSON payload to the game server
int client_send(char *message);

// client loop for threading
int client_loop();

// recv a message from the game server
char *client_recv();

// handle incoming server messages
void handle_incoming();

#endif