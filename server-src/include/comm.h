//
// Created by Maxwell Babey on 10/5/22.
//

#ifndef SERVER_SRC_COMM_H
#define SERVER_SRC_COMM_H

#include "server.h"

/**
 * recv_clients
 * <p>
 * While the running flag is set, accept connections from clients. Receive information from
 * clients and store that information in client-specific directories.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 */
void recv_clients(struct server_settings *set);

#endif //SERVER_SRC_COMM_H
