//
// Created by Maxwell Babey on 10/11/22.
//

#ifndef SERVER_SAVE_H
#define SERVER_SAVE_H

#include <stdint.h>

/**
 * create_dir_str
 * <p>
 * Append to the string stored as the write directory the IP address of the connected client.
 * Store this string in a new string pointer, preserving the base write directory string stored in
 * server_settings for the next client.
 * </p>
 * @param save_dir - char **: pointer to the string to hold the write directory for this client
 * @param wr_dir - char *: the base write directory stored in server_settings
 * @param client_addr_str - char*: the client's IP address
 */
void create_dir_str(char **save_dir, const char *wr_dir, const char *client_addr_str);

/**
 * create_dir
 * <p>
 * Create the directory path specified by the string save_dir.
 * </p>
 * @param save_dir - char *: the directory path to which files will be saved for this client
 */
void create_dir(const char *save_dir);

/**
 * write_to_dir
 * <p>
 * Save the file information in data_buffer to the directory path specified by save_dir under
 * the name file_name.
 * </p>
 * @param save_dir - char *: the directory to which the file will be saved
 * @param file_name - char *: the name of the file
 * @param data_buffer - char *: the file information
 * @param data_buf_size - uint32_t: the size of the file
 */
void write_to_dir(char *save_dir, const char *file_name, const char *data_buffer, uint32_t data_buf_size);


#endif //SERVER_SAVE_H
