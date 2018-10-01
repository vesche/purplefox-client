#ifndef JSON_H_
#define JSON_H_

#include "cJSON.h"

// create payload for login
char *payload_login(char *arg_password);

// create payload for player movement
char *payload_move(char *arg_direction);

#endif