//
// Created by Maxwell Babey on 10/3/22.
//

#ifndef COMP3980ASS2_UTIL_H
#define COMP3980ASS2_UTIL_H

#include "server.h"

/**
 * cleanup
 * <p>
 * Free dynamically allocated memory in server settings.
 * </p>
 * @param sets - server_settings *: pointer to the settings for this server
 */
void cleanup(struct server_settings *sets);

/**
 * set_string
 * <p>
 * Set a string to a value. If the string is NULL, will call malloc. If the string is not NULL, will call
 * realloc.
 * </p>
 * <p>
 * NOTE: Requires a dynamically allocated or NULL first parameter.
 * </p>
 * <p>
 * <h3>
 * WARNING: set_string dynamically allocates memory. Must free the pointer passed as the first parameter!
 * </h3>
 * </p>
 * @param str - char**: pointer to the string to be set
 * @param new_str - char*: the new value for the string
 */
void set_string(char **str, const char *new_str);

/**
 * prepend_string
 * <p>
 * Prepend a prefix to a string.
 * </p>
 * <p>
 * NOTE: Requires a dynamically allocated or NULL first parameter.
 * </p>
 * @param str - char**: pointer to the string to be modified
 * @param prefix - char*: the string to be prepended
 */
void prepend_string(char **str, const char *prefix);

/**
 * append_string
 * <p>
 * Append a suffix to a string.
 * </p>
 * <p>
 * NOTE: Requires a dynamically allocated or NULL first parameter.
 * </p>
 * @param str - char**: pointer to the string to be modified
 * @param suffix - char*: the string to be appended
 */
void append_string(char **str, const char *suffix);

#endif //COMP3980ASS2_UTIL_H
