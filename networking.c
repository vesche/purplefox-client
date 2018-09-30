#include <SDL2/SDL.h>
#include <stdio.h> // tmp
#include <string.h>

#include "networking.h"
#include "error.h"
#include "cJSON.h"

const char *server_addr = "localhost";
const int server_port = 1234;
TCPsocket sock;
SDLNet_SocketSet set = 0;

// tmp?
int disconnected = 0;

void connect_to_server()
{
	IPaddress ip;
	set = SDLNet_AllocSocketSet(1);
	if (!set) {
		// TODO: cleanup on these error out (SDL_Quit, etc)
		//       also standardize error return codes?
		print_error_msg(ERROR_TYPE_NET, "Couldn't allocate socket");
		exit(1);
	}

	if (SDLNet_ResolveHost(&ip, server_addr, server_port) == -1) {
		print_error_msg(ERROR_TYPE_NET, "Couldn't resolve host");
		exit(2);
	}

	sock = SDLNet_TCP_Open(&ip);
	if (sock == NULL) {
		print_error_msg(ERROR_TYPE_NET, "Couldn't open socket");
		exit(3);
	}

	if (SDLNet_TCP_AddSocket(set, sock) == -1) {
		print_error_msg(ERROR_TYPE_NET, "Couldn't add socket");
		exit(4);
	}

	// this has been helpful:
	// https://github.com/raduprv/Eternal-Lands/blob/master/multiplayer.c#L475
}

void disconnect_from_server()
{
	SDLNet_TCP_Close(sock);
	disconnected = 1;
	SDLNet_Quit();
}

int client_send(char *message)
{
	char *data = message;
	int len = strlen(message);
	return SDLNet_TCP_Send(sock, data, len);
}

char *client_recv()
{
	int result;

	/*  Note:
		char message[RECV_MAX_LEN];
		"function returns address of local variable"...
		solution from: https://stackoverflow.com/a/12380788
	*/
	char *message = malloc(sizeof(char) * RECV_MAX_LEN);
	
	result = SDLNet_TCP_Recv(sock, message, RECV_MAX_LEN);
	
	if (result <= 0) {
		// TODO: Change this.
		printf("WARN: result 0 from client_recv\n");
	}

	return message;
}

int client_loop()
{
	int i;
	i = 0;

	for (;;) {
		i++;
		printf("Server has listened for %d messages.\n", i);


		if (disconnected) {
			printf("DEBUG: disconnected is 1");
			break;
		} else if (SDLNet_CheckSockets(set, 100) <= 0 || !SDLNet_SocketReady(sock)) {
			// if no data loop and check again, with 100ms delay time
			continue;
		}

		// tmp?
		// https://github.com/raduprv/Eternal-Lands/blob/master/multiplayer.c#L2332
		
		// SDL_Delay(100); // ten times a second
		// probably shouldn't need this now ^^

		char *response = client_recv();
		if (response)
			handle_incoming(response);
	}
	
	return 1;
}

void handle_incoming(char *message)
{
	const cJSON *command = NULL;

	cJSON *json = cJSON_Parse(message);
	if (json == NULL) {
		print_error_msg(ERROR_TYPE_JSON, "Couldn't parse incoming JSON");
		goto end;
	}

	command = cJSON_GetObjectItemCaseSensitive(json, "command");
	if (!cJSON_IsNumber(command)) {
		print_error_msg(ERROR_TYPE_JSON, "Invalid command type on incoming JSON");
		goto end;
	}

	unsigned int cmd = command->valueint;

	switch(cmd) {
		case CMD_LOCATIONS:
			printf("LOCATIONS COMMAND HERE\n");
			break;
		case CMD_TEST:
			printf("TEST COMMAND HERE\n");
			break;
	}

end:
	cJSON_Delete(json);
	return;
}