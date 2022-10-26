//
// Created by Maxwell Babey on 10/3/22.
//

#include "server.h"
#include "error.h"
#include "util.h"
#include <arpa/inet.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * The default port.
 */
#define DEFAULT_PORT 5000

/**
 * The default write directory.
 */
#define DEFAULT_WR_DIR "/server/downloads"

/**
 * set_simple_defaults
 * <p>
 * Zero the memory in server_settings. Set the default port.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 */
void set_simple_defaults(struct server_settings *set);

/**
 * read_args
 * <p>
 * Read command line arguments and set values in server_settings appropriately
 * </p>
 * @param argc - int: the number of command line arguments
 * @param argv - char **: the command line arguments
 * @param set - server_settings *: pointer to the settings for this server
 */
void read_args(int argc, char *argv[], struct server_settings *set);

/**
 * open_server
 * <p>
 * Create a socket, bind the IP specified in server_settings to the socket, then listen on the socket.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 */
void open_server(struct server_settings *set);

/**
 * parse_port
 * <p>
 * Check the user input port number to ensure it is within parameters. Namely, that it is not
 * larger than 65535.
 * </p>
 * @param buffer - char *: string containing the port number
 * @param base - int: base in which to interpret the port number
 * @return the port number, an in_port_t
 * @author D'Arcy Smith
 */
in_port_t parse_port(const char *buffer, int base);

/**
 * check_ip
 * <p>
 * Check the user input IP address to ensure it is within parameters. Namely, that none of its
 * period separated numbers are larger than 255, and that the address is in the form
 * XXX.XXX.XXX.XXX
 * </p>
 * @param ip - char *: the string containing the IP address
 * @param base - int: base in which to interpret the IP address
 */
void check_ip(char *ip, int base);

/**
 * set_self_ip.
 * <p>
 * Get this host's IP address and attach it to the parameter char pointer pointer.
 * </p>
 * @param ip - char**: pointer to pointer to first char in IP address.
 */
void set_self_ip(char **ip);

/**
 * set_wr_dir
 * <p>
 * Sets the write directory for this server. Call functions to modify the user-specified path
 * into a machine-readable format.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 */
void set_wr_dir(struct server_settings *set);

/**
 * fix_dir_end
 * <p>
 * If a user specifies a save directory with "//" at any point, truncate the path at the first '/'.
 * If a user specifies a save directory ending with '/', remove the last character.
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 */
void fix_dir_end(const struct server_settings *set);

/**
 * fix_dir_start
 * <p>
 * Modifies the user-specified save directory's beginning. This function will:
 * <ul>
 * <li>Convert "~" to the home directory path,</li>
 * <li>Prepend the home path if no path to the directory is specified, or</li>
 * <li>Leave directories starting with "." or "/" as they are.</li>
 * </ul>
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 */
void fix_dir_start(struct server_settings *set);

/**
 * set_def_wr_dir
 * <p>
 * Set the save directory to the server-specified default: "Users/user/server/downloads"
 * </p>
 * @param set - server_settings *: pointer to the settings for this server
 */
void set_def_wr_dir(struct server_settings *set);

void run_server(int argc, char *argv[], struct server_settings *set)
{
    set_simple_defaults(set);
    read_args(argc, argv, set);
    open_server(set);
}

void set_simple_defaults(struct server_settings *set)
{
    memset(set, 0, sizeof(struct server_settings)); // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) : Not a POSIX function
    set->port = DEFAULT_PORT;
}

void read_args(int argc, char *argv[], struct server_settings *set)
{
    const int base = 10;
    int c;

    while ((c = getopt(argc, argv, ":s:d:p:")) != -1) // NOLINT(concurrency-mt-unsafe) : No threads here
    {
        switch (c)
        {
            case 's':
            {
                check_ip(optarg, base);
                set->ip = optarg;
                break;
            }
            case 'd':
            {
                set_wr_dir(set);
                break;
            }
            case 'p':
            {
                set->port = parse_port(optarg, base);
                break;
            }
            case ':':
            {
                fatal_message(__FILE__, __func__, __LINE__, "\"Option requires an operand\"",
                              5); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            }
            case '?':
            {
                fatal_message(__FILE__, __func__, __LINE__, "Unknown",
                              6); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
            }
            default:
            {
                fatal_message(__FILE__, __func__, __LINE__, "\nYou shouldn't be here.\n",
                              69); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers) : 69 is a very magic number
            }
        }
    }
    if (set->wr_dir == NULL)
    {
        set_def_wr_dir(set);
    }
    if (set->ip == NULL)
    {
        set_self_ip(&set->ip);
    }
}

void check_ip(char *ip, int base)
{
    const char *msg;
    char *ip_cpy = NULL;
    char *end;
    char *tok;
    char delim[2] = ".";
    int tok_count;
    long num;
    errno = 0;

    set_string(&ip_cpy, ip);

    tok = strtok(ip_cpy, delim); // NOLINT(concurrency-mt-unsafe) : No threads here
    tok_count = 0;
    while (tok != NULL)
    {
        ++tok_count;

        num = strtol(tok, &end, base);

        if (end == tok)
        {
            msg = "not a decimal number";
        } else if (*end != '\0')
        {
            msg = "%s: extra characters at end of input";
        } else if ((LONG_MIN == num || LONG_MAX == num) && ERANGE == errno)
        {
            msg = "out of range of type long";
        } else if (num > UINT8_MAX)
        {
            msg = "greater than UINT8_MAX";
        } else if (num < 0)
        {
            msg = "less than 0";
        } else
        {
            msg = NULL;
        }

        if (msg)
        {
            fatal_message(__FILE__, __func__, __LINE__, msg, 2);
        }

        tok = strtok(NULL, delim); // NOLINT(concurrency-mt-unsafe) : No threads here
    }
    if (tok_count != 4)
    {
        fatal_message(__FILE__, __func__, __LINE__, "IP address must be in form XXX.XXX.XXX.XXX\n", 2);
    }
    free(ip_cpy);
}

in_port_t parse_port(const char *buffer, int base)
{
    char *end;
    long sl;
    in_port_t port;
    const char *msg;

    errno = 0;
    sl = strtol(buffer, &end, base);

    if (end == buffer)
    {
        msg = "not a decimal number";
    } else if (*end != '\0')
    {
        msg = "%s: extra characters at end of input";
    } else if ((LONG_MIN == sl || LONG_MAX == sl) && ERANGE == errno)
    {
        msg = "out of range of type long";
    } else if (sl > UINT16_MAX)
    {
        msg = "greater than UINT16_MAX";
    } else if (sl < 0)
    {
        msg = "less than 0";
    } else
    {
        msg = NULL;
    }
    if (msg)
    {
        fatal_message(__FILE__, __func__, __LINE__, msg, 2);
    }

    port = (in_port_t) sl;

    return port;
}

void set_self_ip(char **ip)
{
    struct addrinfo hints;
    struct addrinfo *results;
    struct addrinfo *res_next;
    char *hostname;
    const size_t hostname_buf = 128;

    hostname = (char *) malloc(hostname_buf);
    gethostname(hostname, hostname_buf);

    memset(&hints, 0, sizeof(struct addrinfo)); // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) : Not a POSIX function
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(hostname, NULL, &hints, &results) != 0)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }

    for (res_next = results; res_next != NULL; res_next = res_next->ai_next)
    {
        *ip = inet_ntoa(((struct sockaddr_in *) res_next->ai_addr)->sin_addr); // NOLINT(concurrency-mt-unsafe, clang-diagnostic-cast-align, Wcast-align) : No threads here, upcast intentional
    }

    free(hostname);
    freeaddrinfo(results);
}

void set_wr_dir(struct server_settings *set)
{
    set_string(&set->wr_dir, optarg);

    fix_dir_end(set);
    if (*set->wr_dir != '/' && *(set->wr_dir + 1) != '\0')
    {
        fix_dir_start(set);
    }
    printf("Write directory set to: \'%s\'\n", set->wr_dir);
}

void fix_dir_end(const struct server_settings *set)
{
    size_t len;
    if (*set->wr_dir == '/' && *(set->wr_dir + 1) == '/')
    {
        *(set->wr_dir + 1) = '\0';
        return;
    }
    len = strlen(set->wr_dir);
    for (size_t i = 1; i < len; ++i)
    {
        if ((*(set->wr_dir + i) == '/' && *(set->wr_dir + i + 1) == '/') ||
                (*(set->wr_dir + i) == '/' && *(set->wr_dir + i + 1) == '\0'))
        {
            *(set->wr_dir + i) = '\0';
        }
    }
}

void fix_dir_start(struct server_settings *set)
{
    char *homdir = getenv("HOME"); // NOLINT(concurrency-mt-unsafe) : No threads here
    if (*optarg == '~' && *(optarg + 1) == '/')
    {
        char *home_fix = NULL;
        set_string(&home_fix, set->wr_dir + 1);
        prepend_string(&home_fix, homdir);
        set_string(&set->wr_dir, home_fix);
        free(home_fix);
    } else if (*optarg != '.' && *optarg != '/')
    {
        prepend_string(&set->wr_dir, "/");
        prepend_string(&set->wr_dir, homdir);
    }
}

void set_def_wr_dir(struct server_settings *set)
{
    char *homdir = getenv("HOME"); // NOLINT(concurrency-mt-unsafe) : No threads here
    set_string(&set->wr_dir, DEFAULT_WR_DIR);
    prepend_string(&set->wr_dir, homdir);
}

void open_server(struct server_settings *set)
{
    struct sockaddr_in host_addr;
    int sock_option;
    const int backlog = 5;

    if ((set->fd_listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) // NOLINT(android-cloexec-socket) : SOCK_CLOEXEC dne
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(set->port);
    if ((host_addr.sin_addr.s_addr = inet_addr(set->ip)) == (in_addr_t) -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 2);
    }

    sock_option = 1;
    setsockopt(set->fd_listen_sock, SOL_SOCKET, SO_REUSEADDR, &sock_option, sizeof(sock_option));

    if (bind(set->fd_listen_sock, (struct sockaddr *) &host_addr, sizeof(struct sockaddr_in)) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }

    if (listen(set->fd_listen_sock, backlog) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
}
