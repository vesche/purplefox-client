#include <stdio.h>

#include "payloads.h"

/*
{
    "username": "vesche",
    "command": "move",
    "arguments": {
        "x": 13,
        "y": 37
    }
}
*/

// temporary until I have a global.h or something
const char *USERSTR = "vesche";

cJSON *payload_init(char *CMDSTR)
{
    cJSON *username = NULL;
    cJSON *command = NULL;

    cJSON *payload = cJSON_CreateObject();

    username = cJSON_CreateString(USERSTR);
    cJSON_AddItemToObject(payload, "username", username);
    command = cJSON_CreateString(CMDSTR);
    cJSON_AddItemToObject(payload, "command", command);

    return payload;
}

char *payload_login(char *arg_password)
{
    char *string = NULL;

    char *CMDSTR = "login";
    cJSON *payload = payload_init(CMDSTR);

    cJSON *arguments = NULL;
    cJSON *password = NULL;

    arguments = cJSON_CreateObject();
    password = cJSON_CreateString(arg_password);
    cJSON_AddItemToObject(arguments, "password", password);
    cJSON_AddItemToObject(payload, "arguments", arguments);

    string = cJSON_Print(payload);
    cJSON_Delete(payload);
    return string;
}

char *payload_move(char *arg_direction)
{
    char *string = NULL;

    char *CMDSTR = "move";
    cJSON *payload = payload_init(CMDSTR);

    cJSON *arguments = NULL;
    cJSON *direction = NULL;

    arguments = cJSON_CreateObject();
    direction = cJSON_CreateString(arg_direction);
    cJSON_AddItemToObject(arguments, "direction", direction);
    cJSON_AddItemToObject(payload, "arguments", arguments);

    string = cJSON_Print(payload);
    cJSON_Delete(payload);
    return string;
}