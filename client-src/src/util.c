//
// Created by Maxwell Babey on 10/9/22.
//

#include "util.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

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
