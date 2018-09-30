
/*
    Code dump
*/

/* testing networking.h

SDL_Delay(1000);

char *message_a = payload_login("test");
client_send(message_a);

// NOTE: there needs to be a SDL_Delay before sending new messaages to the server
SDL_Delay(10);

char *message_b = payload_move(13, 37);
client_send(message_b);

char *response = client_recv();
handle_incoming(response);
*/

/* testing sprites
SDL_Surface *sprite;
sprite = SDL_DisplayFormat(surface);
SDL_Rect player;
player.x = 0;
player.y = 0;
*/

int main()
{
    return 0;
}