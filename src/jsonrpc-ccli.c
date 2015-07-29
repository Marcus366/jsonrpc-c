#include "jsonrpc-ccli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

static int __jrpc_parse_addr(const char *addr,
        struct sockaddr_in *sockaddr);

int jrpc_syncli_connect(struct jrpc_sync_client * client, const char *addr) {
    int port, return_value;
    struct sockaddr_in sockaddr;

    memset(client, 0, sizeof(client));

    return_value = __jrpc_parse_addr(addr, &sockaddr);
    if (return_value != 0) {
        client->error_message = "parse addr error";
        return -1;
    }

    if ((client->fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        return client->fd;
    }

    if (connect(client->fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) != 0) {
        return -1;
    }

    return 0;
}

int jrpc_syncli_close(struct jrpc_sync_client * client) {
    close(client->fd);
    free(client->buffer);
    return 0;
}

int jrpc_syncli_call(struct jrpc_sync_client * client,
        char *name, cJSON **param) {
    int return_value;
    char *content, *p;
    size_t len;
    ssize_t nbytes;
    cJSON *root, *method, *id;

    root = cJSON_CreateObject();
    method = cJSON_CreateString(name);
    id = cJSON_CreateNumber(rand());
    cJSON_AddItemToObject(root, "method", method);
    cJSON_AddItemToObject(root, "param", *param);

    client->buffer = cJSON_PrintUnformatted(root);
    client->buffer_size = strlen(client->buffer);
    cJSON_Delete(root);

    p = client->buffer;
    len = client->buffer_size;
    while (len && (nbytes = write(client->fd, p, len)) > 0) {
        p += nbytes;
        len -= nbytes;
    }

    *param = NULL;
    p = client->buffer;
    len = client->buffer_size;
    bzero(p, len);
    while ((nbytes = read(client->fd, p, len)) > 0) {
        p += nbytes;
        len -= nbytes;

        *param = cJSON_Parse(client->buffer);
        if (*param != NULL) {
            if ((*param)->type == cJSON_Object) {
              break;
            }
        }

        if (len == 0) {
            len = client->buffer_size;
            client->buffer_size <<= 1;
            client->buffer = (char*)realloc(client->buffer, client->buffer_size);
        }
    }

    return 0;
}

int __jrpc_parse_addr(const char *addr,
        struct sockaddr_in *sockaddr) {
    int val[4];
    int ipv4, port;

    ipv4 = sscanf(addr, "%d.%d.%d.%d:%d",
        &val[0], &val[1], &val[2], &val[3], &port);
    if (ipv4 != 5) {
        return -1;
    }

    ipv4 = val[0] << 24 | val[1] << 16 | val[2] << 8 | val[3];

    sockaddr->sin_family = AF_INET;
    sockaddr->sin_port = htons(port);
    sockaddr->sin_addr.s_addr = htonl(ipv4);

    return 0;
}
