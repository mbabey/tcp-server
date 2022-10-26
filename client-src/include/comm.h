//
// Created by Maxwell Babey on 10/5/22.
//

#ifndef CLIENT_SRC_COMM_H
#define CLIENT_SRC_COMM_H

#include "client.h"

/**
 * send_files
 * <p>
 * Send files to the server specified in client_settings.
 * </p>
 * @param argc - int: the number of command line arguments
 * @param argv - char **: the command line arguments
 * @param set - client_settings *: pointer to the settings for this client
 */
void send_files(int argc, char *argv[], struct client_settings *set);

#endif //CLIENT_SRC_COMM_H
