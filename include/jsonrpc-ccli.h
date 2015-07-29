#ifndef JSONRPCCCLI_H_
#define JSONRPCCCLI_H_

#include "jsonrpc-c.h"

typedef int (*jrpc_cli_function)(jrpc_context *context, cJSON *params, cJSON* id);

struct jrpc_sync_client {
    int fd;
    unsigned int buffer_size;
    char * buffer;
    char * error_message;
};

int jrpc_syncli_connect(struct jrpc_sync_client * client, const char *addr);
int jrpc_syncli_close(struct jrpc_sync_client * client);

int jrpc_syncli_call(
    struct jrpc_sync_client * client,
    char *name,    /* [IN] method name */
    cJSON **param  /* [IN|OUT] request params | response result */
    );


#endif
