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