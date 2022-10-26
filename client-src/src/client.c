//
// Created by Maxwell Babey on 10/4/22.
//

#include "client.h"
#include "error.h"
#include "util.h"
#include <arpa/inet.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define DEFAULT_PORT 5000

/**
 * set_simple_defaults
 * <p>
 * Zero the memory in client_settings. Set the default port.
 * </p>
 * @param set - client_settings *: pointer to the settings for this server
 */
void set_simple_defaults(struct client_settings *set);

/**
 * read_args
 * <p>
 * Read command line arguments and set values in client_settings appropriately
 * </p>
 * @param argc - int: the number of command line arguments
 * @param argv - char **: the command line arguments
 * @param set - client_settings *: pointer to the settings for this server
 */
void read_args(int argc, char *argv[], struct client_settings *set);

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
 * connect_client
 * <p>
 * Creates a socket and connects to a server specified by the port number and IP address in
 * client_settings.
 * </p>
 * @param set - client_settings *: pointer to the settings for this server
 */
void connect_client(struct client_settings *set);

void run_client(int argc, char *argv[], struct client_settings *set)
{
    set_simple_defaults(set);
    read_args(argc, argv, set);
    connect_client(set);
}

void set_simple_defaults(struct client_settings *set)
{
    memset(set, 0, sizeof(struct client_settings)); // NOLINT(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling) : Not a POSIX function
    set->server_port = DEFAULT_PORT;
}

void read_args(int argc, char *argv[], struct client_settings *set)
{
    const int base = 10;
    int c;

    while ((c = getopt(argc, argv, ":s:p:")) != -1) // NOLINT(concurrency-mt-unsafe) : No threads here
    {
        switch (c)
        {
            case 's':
            {
                check_ip(optarg, base);
                set->server_ip = optarg;
                break;
            }
            case 'p':
            {
                set->server_port = parse_port(optarg, base);
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
    if (set->server_ip == NULL)
    {
        fatal_message(__FILE__, __func__, __LINE__, "Usage: client -s <ip-address> -p <port> <files...>", 2);
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

void connect_client(struct client_settings *set)
{
    struct sockaddr_in addr;

    if ((set->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) // NOLINT(android-cloexec-socket) : SOCK_CLOEXEC dne
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(set->server_port);
    addr.sin_addr.s_addr = inet_addr(set->server_ip);

    if (addr.sin_addr.s_addr == (in_addr_t) -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 2);
    }

    if (connect(set->server_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1)
    {
        fatal_errno(__FILE__, __func__, __LINE__, errno, 4);
    }
}
