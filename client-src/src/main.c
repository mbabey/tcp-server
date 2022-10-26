#include "client.h"
#include "comm.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main
 * <p>
 * Drives the program.
 * </p>
 * <p>
 * Boot up the client, then send files.
 * </p>
 * @param argc - int: number of command line arguments
 * @param argv - char**: command line arguments
 * @return 0 on successful execution
 */
int main(int argc, char *argv[])
{
    struct client_settings set;

    run_client(argc, argv, &set);
    printf("Connected to %s:%d\n", set.server_ip, set.server_port);
    send_files(argc, argv, &set);

    close(set.server_fd);

    return EXIT_SUCCESS;
}
