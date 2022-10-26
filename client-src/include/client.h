//
// Created by Maxwell Babey on 10/4/22.
//

#ifndef CLIENT_SRC_CLIENT_H
#define CLIENT_SRC_CLIENT_H

#include <netinet/in.h>
#include <sys/types.h>

/**
 * client_settings
 * <p>
 * Struct storing the settings for the server to which this client will connect.
 * <ul>
 * <li>char *server_ip: the IP address of the server</li>
 * <li>in_port_t server_port: the port number of the server</li>
 * <li>int server_fd: file descriptor for socket of connected server</li>
 * </ul>
 * </p>
 */
struct client_settings
{
    char *server_ip;
    in_port_t server_port;
    int server_fd;
};

/**
 * run_client
 * <p>
 * Assign settings to this client based on defaults and command line arguments.
 * Then, start the client.
 * </p>
 * @param argc - int: number of command line arguments
 * @param argv - char **: command line arguments
 * @param set - client_settings *: pointer to the settings for this client
 */
void run_client(int argc, char *argv[], struct client_settings *set);

#endif //CLIENT_SRC_CLIENT_H
