
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

/*
char *payload_move(int arg_x, int arg_y)
{
    char *string = NULL;

    char *CMDSTR = "move";
    cJSON *payload = payload_init(CMDSTR);

    cJSON *arguments = NULL;
    cJSON *x = NULL;
    cJSON *y = NULL;

    arguments = cJSON_CreateObject();
    x = cJSON_CreateNumber(arg_x);
    y = cJSON_CreateNumber(arg_y);
    cJSON_AddItemToObject(arguments, "x", x);
    cJSON_AddItemToObject(arguments, "y", y);
    cJSON_AddItemToObject(payload, "arguments", arguments);

    string = cJSON_Print(payload);
    cJSON_Delete(payload);
    return string;
}
*/

int main()
{
    return 0;
}