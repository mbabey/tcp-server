//
// Created by Maxwell Babey on 10/5/22.
//

#include "comm.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * send_file_name
 * <p>
 * Send the file name to the server:
 * <ol>
 * <li>Get the length of the file name (f_name_len),</li>
 * <li>Send 2 bytes as the length of the file name,</li>
 * <li>Send f_name_len bytes as the file name.</li>
 * </ol>
 * </p>
 * @param file_name - char*: the file name
 * @param set - client_settings *: pointer to the settings for this client
 */
void send_file_name(const char *file_name, const struct client_settings *set);

/**
 * get_f_data_len
 * <p>
 * Get the length of the file at file_name.
 * </p>
 * @param file_name - char *: the name of the file for which to get the length
 * @return the length of the file
 */
uint32_t get_f_data_len(const char *file_name);

/**
 * send_file_data
 * <p>
 * Send the file data to the server:
 * <ol>
 * <li>Get the size of the file (f_data_len),</li>
 * <li>Send 4 bytes as the length of the file,</li>
 * <li>Read the file information into a buffer of f_data_len size,</li>
 * <li>Send f_data_len bytes of buffer as the file.</li>
 * </ol>
 * </p>
 * @param file_name - char*: the file name
 * @param set - client_settings *: pointer to the settings for this client
 */
void send_file_data(const char *file_name, const struct client_settings *set);

/**
 * read_file
 * <p>
 * Creates a buffer of f_data_len size, then reads the file at file_name into that buffer.
 * </p>
 * @param file_name - char*: the file name
 * @param f_data_len - uint32_t: the length of the file
 * @param data_buffer - char **: pointer to buffer to hold file data
 */
void read_file(const char *file_name, uint32_t f_data_len, char **file_data);

void send_files(int argc, char *argv[], struct client_settings *set)
{
    while (argc > optind)
    {
        send_file_name(argv[optind], set);

        send_file_data(argv[optind], set);

        printf("Sent to server: %s\n", argv[optind]);

        optind++;
    }
}

void send_file_name(const char *file_name, const struct client_settings *set)
{
    uint16_t filename_size;
    ssize_t ret_val;
    ssize_t bytes_sent = 0;

    // Send the length of the file name
    filename_size = strlen(file_name);
    filename_size = htons(filename_size);
    if (send(set->server_fd, &filename_size, sizeof(uint16_t), 0) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
    filename_size = ntohs(filename_size);

    // Send the file name
    while (bytes_sent < filename_size)
    {
        if ((ret_val = send(set->server_fd, &file_name[bytes_sent], filename_size, 0)) == -1)
        {
            fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
        }
        bytes_sent += ret_val;
    }
}

void send_file_data(const char *file_name, const struct client_settings *set)
{
    uint32_t f_data_len;
    char *file_data;
    ssize_t ret_val;
    ssize_t bytes_sent = 0;

    // Send the file length
    f_data_len = get_f_data_len(file_name);
    f_data_len = htonl(f_data_len);
    if (send(set->server_fd, &f_data_len, sizeof(uint32_t), 0) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
    f_data_len = ntohl(f_data_len);

    // Read the file data into a buffer
    read_file(file_name, f_data_len, &file_data);

    // Send the buffer of file data
    while (bytes_sent < f_data_len)
    {
        if ((ret_val = send(set->server_fd, file_data + bytes_sent, f_data_len - bytes_sent, 0)) == -1)
        {
            fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
        }
        bytes_sent += ret_val;
    }

    free(file_data);
}

uint32_t get_f_data_len(const char *file_name)
{
    uint32_t f_data_len;
    struct stat st;
    if (stat(file_name, &st) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
    f_data_len = st.st_size;
    return f_data_len;
}

void read_file(const char *file_name, uint32_t f_data_len, char **file_data)
{
    int fd_ofile;
    if ((fd_ofile = open(file_name, O_RDONLY | O_CLOEXEC)) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
    if ((*file_data = (char *) calloc(f_data_len + 1, sizeof(char))) == NULL)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }
    if (read(fd_ofile, *file_data, f_data_len) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
    close(fd_ofile);
}
