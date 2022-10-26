//
// Created by Maxwell Babey on 10/11/22.
//

#include "error.h"
#include "save.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define VERSION_START_INDEX 2

#define WR_DIR_FLAGS (S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)

/**
 * version_file
 * <p>
 * Add a version number to a file name, if necessary.
 * </p>
 * @param save_str - char **: file name to which a version number will be added.
 */
void version_file(char **save_str);

/**
 * create_file_ver_suffix
 * <p>
 * Create a string in the format "-v2".
 * </p>
 * @param file_ver_suffix - char **: pointer to string to hold the suffix
 * @param v_num - int: the version number to put in the suffix
 */
void create_file_ver_suffix(char **file_ver_suffix, int v_num);

void create_dir_str(char **save_dir, const char *wr_dir, const char *client_addr_str) // NOLINT(bugprone-easily-swappable-parameters)
{
    set_string(save_dir, wr_dir);
    append_string(save_dir, "/");
    append_string(save_dir, client_addr_str);
}

void create_dir(const char *save_dir)
{
    char *path;
    size_t len;

    len = strlen(save_dir);
    if ((path = (char *) calloc(len + 1, sizeof(char))) == NULL)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }

    for (size_t index = 0; index < len; ++index)
    {
        *(path + index) = *(save_dir + index);
        if (index < len && (*(save_dir + index + 1) == '/' || *(save_dir + index + 1) == '\0'))
        {
            if (access(path, F_OK) != 0)
            {
                if ((mkdir(path, WR_DIR_FLAGS)) == -1)
                {
                    fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
                }
            }
        }
    }
    free(path);
}

void write_to_dir(char *save_dir, const char *file_name, const char *data_buffer, uint32_t data_buf_size) // NOLINT(bugprone-easily-swappable-parameters)
{
    char *save_file_name = NULL;
    int save_fd;

    set_string(&save_file_name, save_dir);
    append_string(&save_file_name, "/");
    append_string(&save_file_name, file_name);

    version_file(&save_file_name);

    if ((save_fd = open(save_file_name, O_CREAT | O_WRONLY | O_CLOEXEC, WR_DIR_FLAGS)) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }

    if (write(save_fd, data_buffer, data_buf_size) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }

    free(save_file_name);
}

void version_file(char **save_str)
{
    int v_num = VERSION_START_INDEX;
    char *file_ver_suffix = NULL;
    char *save_str_cpy = NULL;
    char *ext = NULL;
    char *ext_ptr;

    set_string(&save_str_cpy, *save_str);

    while (access(save_str_cpy, F_OK) == 0) // does exist
    {
        if (v_num > VERSION_START_INDEX)
        {
            set_string(&save_str_cpy, *save_str);
        }

        ext_ptr = strrchr(save_str_cpy, '.');
        set_string(&ext, ext_ptr);

        create_file_ver_suffix(&file_ver_suffix, v_num);

        *ext_ptr = '\0';
        append_string(&save_str_cpy, file_ver_suffix);
        append_string(&save_str_cpy, ext);

        ++v_num;
    }
    set_string(save_str, save_str_cpy);

    free(file_ver_suffix);
    free(save_str_cpy);
    free(ext);
}

void create_file_ver_suffix(char **file_ver_suffix, int v_num)
{
    int v_num_len;
    char *v_num_suffix = NULL;

    if ((v_num_len = snprintf(NULL, 0, "%d", v_num)) < 0) // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) : Not a POSIX function
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }
    if ((v_num_suffix = (char *) calloc(v_num_len + 1, sizeof(char))) == NULL)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }
    if (snprintf(v_num_suffix, v_num_len + 1, "%d", v_num) < 0) // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) : Not a POSIX function
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 3);
    }

    set_string(file_ver_suffix, "-v");
    append_string(file_ver_suffix, v_num_suffix);

    free(v_num_suffix);
}
