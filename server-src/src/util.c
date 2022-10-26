//
// Created by Maxwell Babey on 10/3/22.
//

#include "util.h"
#include "error.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

void cleanup(struct server_settings *sets)
{
    close(sets->fd_listen_sock);
}

void set_string(char **str, const char *new_str)
{
    size_t buf = strlen(new_str) + 1;

    if (!*str) // Double negative: true if the string is NULL
    {
        if((*str = (char *) malloc(buf)) == NULL)
        {
            fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
        }
    } else
    {
        if ((*str = (char *) realloc(*str, buf)) == NULL)
        {
            fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
        }
    }

    strcpy(*str, new_str);
}

void prepend_string(char **str, const char *prefix)
{
    char *new_str;
    size_t str_buf = strlen(*str) + 1;
    size_t prefix_size = strlen(prefix);

    if ((new_str = (char *) calloc(str_buf + prefix_size, sizeof(char))) == NULL)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }

    strcat(new_str, prefix);
    strcat(new_str, *str);
    set_string(str, new_str);

    free(new_str);
}

void append_string(char **str, const char *suffix)
{
    char *new_str;
    size_t str_buf = strlen(*str) + 1;
    size_t suffix_size = strlen(suffix);

    if ((new_str = (char *) calloc(str_buf + suffix_size, sizeof(char))) == NULL)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }

    strcat(new_str, *str);
    strcat(new_str, suffix);
    set_string(str, new_str);

    free(new_str);
}
