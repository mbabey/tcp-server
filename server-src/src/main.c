#include "server.h"
#include "comm.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * main
 * <p>
 * Drives the program.
 * </p>
 * <p>
 * Boot up the server, then receive files.
 * </p>
 * @param argc - int: number of command line arguments
 * @param argv - char**: command line arguments
 * @return 0 on successful execution
 */
int main(int argc, char *argv[])
{
    struct server_settings set;

    run_server(argc, argv, &set);
    printf("Server IP: %s\nServer port: %d\n", set.ip, set.port);
    recv_clients(&set);

    cleanup(&set);

    return EXIT_SUCCESS;
}
