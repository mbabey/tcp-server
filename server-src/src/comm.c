//
// Created by Maxwell Babey on 10/5/22.
//

#include "comm.h"
#include "error.h"
#include "save.h"
#include "util.h"
#include <arpa/inet.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @author D'Arcy Smith
 */
static volatile sig_atomic_t running;   // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

/**
 * recv_files
 * <p>
 * While a client is sending information, loop through receiving byte data as per the following protocol:
 * <ul>
 * <li>Receive 2 bytes as the [file-name-length]</li>
 * <li>Receive [file-name-length] bytes as the file name</li>
 * <li>Receive 4 bytes as the [file-size]</li>
 * <li>Receive [file-size] bytes as the file data</li>
 * </ul>
 * Then, store the information in a client-specific directory.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 * @param save_dir_str - char *: string holding the directory to which files will be saved
 */
void recv_files(const struct server_settings *set, char *save_dir_str);

/**
 * recv_f_name_len
 * <p>
 * Receive 2 bytes as the file name length.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 * @param f_name_len - uint16_t *: pointer to the memory to hold the file name length
 */
void recv_f_name_len(const struct server_settings *set, uint16_t *f_name_len);

/**
 * recv_file_name
 * <p>
 * Receive f_name_len bytes as the file name.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 * @param f_name_len - uint16_t: the number of bytes to receive
 * @param file_name - char **: pointer to the string to hold the file name
 */
void recv_file_name(const struct server_settings *set, uint16_t f_name_len, char **file_name);

/**
 * recv_f_data_len
 * <p>
 * Receive 4 bytes as the file data length, or file size.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 * @param f_data_len - uint32_t *: pointer to the memory to hold the file size
 */
void recv_f_data_len(const struct server_settings *set, uint32_t *f_data_len);

/**
 * recv_f_data
 * <p>
 * Receive f_data_len bytes as the file data.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 * @param f_data_len - uint32_t: the number of bytes to receive
 * @param data_buffer - char **: pointer to memory to hold the file data
 * @return the number of bytes read; 0 means client disconnect.
 */
ssize_t recv_f_data(const struct server_settings *set, uint32_t f_data_len, char **data_buffer);

/**
 * set_signal_handling
 * @param sa
 * @author D'Arcy Smith
 */
static void set_signal_handling(struct sigaction *sa);

/**
 * signal_handler
 * @param sig
 * @author D'Arcy Smith
 */
static void signal_handler(int sig);

void recv_clients(struct server_settings *set)
{
    struct sigaction sa;

    set_signal_handling(&sa);
    running = 1;

    while (running)
    {
        char *client_addr_str = NULL;
        char *save_dir_str = NULL;
        struct sockaddr_in client_addr;
        in_port_t client_port;
        socklen_t sockaddr_in_size;

        sockaddr_in_size = sizeof(struct sockaddr_in);
        if ((set->fd_client_sock = accept(set->fd_listen_sock, (struct sockaddr *) &client_addr, &sockaddr_in_size)) == -1)  // NOLINT(android-cloexec-accept) : SOCK_CLOEXEC dne
        {
            if (errno == EINTR)
            {
                printf("\n\nClosed server on: %s:%d\n\n", set->ip, set->port);
                cleanup(set);
                exit(EXIT_SUCCESS);   // NOLINT(concurrency-mt-unsafe) : No threads here
            }
            fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
        }

        client_addr_str = inet_ntoa(client_addr.sin_addr);  // NOLINT(concurrency-mt-unsafe) : No threads here
        client_port = ntohs(client_addr.sin_port);

        printf("\n%s:%d connected.\n\n", client_addr_str, client_port);

        create_dir_str(&save_dir_str, set->wr_dir, client_addr_str);
        create_dir(save_dir_str);

        recv_files(set, save_dir_str);

        printf("%s:%d left.\n", client_addr_str, client_port);

        close(set->fd_client_sock);
        free(save_dir_str);
    }
}

void recv_files(const struct server_settings *set, char *save_dir_str)
{
    ssize_t bytes_recv;
    do
    {
        uint16_t f_name_len = 0;
        char *file_name = NULL;
        uint32_t f_data_len = 0;
        char *file_data = NULL;

        // Get the length of the file name
        recv_f_name_len(set, &f_name_len);

        // Get the file name and store the file name in a buffer of file name length + 1 size
        recv_file_name(set, f_name_len, &file_name);

        // Get the file size
        recv_f_data_len(set, &f_data_len);

        // Store the file data in a buffer of file size + 1
        bytes_recv = recv_f_data(set, f_data_len, &file_data);

        if (bytes_recv > 0)
        {
            write_to_dir(save_dir_str, file_name, file_data, f_data_len);
            printf("Received: %s\nSaved to: %s\n\n", file_name, save_dir_str);
        }

        free(file_data);
        free(file_name);
    } while (bytes_recv != 0);
}

void recv_f_name_len(const struct server_settings *set, uint16_t *f_name_len)
{
    if (recv(set->fd_client_sock, f_name_len, sizeof(uint16_t), 0) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
    *f_name_len = ntohs(*f_name_len);
}

void recv_file_name(const struct server_settings *set, const uint16_t f_name_len, char **file_name)
{
    ssize_t ret_val = 1;
    ssize_t bytes_recv = 0;
    if ((*file_name = (char *) calloc(f_name_len + 1, sizeof(char))) == NULL)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }

    while (bytes_recv < f_name_len && ret_val != 0)
    {
        if ((ret_val = recv(set->fd_client_sock, file_name[bytes_recv], f_name_len, 0)) == -1)
        {
            fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
        }
        bytes_recv += ret_val;
    }
}

void recv_f_data_len(const struct server_settings *set, uint32_t *f_data_len)
{
    if (recv(set->fd_client_sock, f_data_len, sizeof(uint32_t), 0) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
    *f_data_len = ntohl(*f_data_len);
}

ssize_t recv_f_data(const struct server_settings *set, const uint32_t f_data_len, char **data_buffer)
{
    ssize_t ret_val = 1;
    ssize_t bytes_recv = 0;
    if ((*data_buffer = (char *) calloc(f_data_len + 1, sizeof(char))) == NULL)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }
    while (bytes_recv < f_data_len && ret_val != 0)
    {
        if ((ret_val = recv(set->fd_client_sock, *data_buffer + bytes_recv, f_data_len - bytes_recv, 0)) == -1)
        {
            fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
        }
        bytes_recv += ret_val;
    }
    return bytes_recv;
}

static void set_signal_handling(struct sigaction *sa)
{
    int result;

    sigemptyset(&sa->sa_mask);
    sa->sa_flags = 0;
    sa->sa_handler = signal_handler;
    result = sigaction(SIGINT, sa, NULL);

    if (result == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 2);
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

static void signal_handler(int sig)
{
    running = 0;
}

#pragma GCC diagnostic pop
