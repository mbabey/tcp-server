//
// Created by Maxwell Babey on 10/3/22.
//

#ifndef COMP3980ASS2_INIT_SERVER_H
#define COMP3980ASS2_INIT_SERVER_H

#include <netinet/in.h>
#include <sys/types.h>

/**
 * server_settings
 * <p>
 * Struct storing the settings for this server.
 * <ul>
 * <li>char *ip: the IP address</li>
 * <li>char *wr_dir: the base save directory for incoming files</li>
 * <li>in_port_t port: the port number</li>
 * <li>int fd_listen_sock: file descriptor for socket listening for connections</li>
 * <li>int fd_client_sock: file descriptor for socket of connected client</li>
 * </ul>
 * </p>
 */
struct server_settings
{
    char *ip;
    char *wr_dir;
    in_port_t port;
    int fd_listen_sock;
    int fd_client_sock;
};

/**
 * run_server
 * <p>
 * Assign settings to this server based on defaults and command line arguments.
 * Then, start the server.
 * </p>
 * @param argc - int: number of command line arguments
 * @param argv - char **: command line arguments
 * @param set - server_settings *: pointer to the settings for this server
 */
void run_server(int argc, char *argv[], struct server_settings *set);

#endif //COMP3980ASS2_INIT_SERVER_H
