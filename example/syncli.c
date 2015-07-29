#include "jsonrpc-ccli.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    int ret;
    struct jrpc_sync_client client;
    cJSON *param = NULL;

    ret = jrpc_syncli_connect(&client, "127.0.0.1:1234");
    if (ret != 0) {
        perror("jrpc_syncli_connect fail");
        exit(-1);
    }

    ret = jrpc_syncli_call(&client, "sayHello", &param);
    if (ret != 0) {
        perror("jrpc_syncli_call fail");
        exit(-1);
    }

    if (param != NULL) {
        printf("%s\n", cJSON_Print(param));
        cJSON_Delete(param);
    } else {
        printf("recv response error\n");
    }
    jrpc_syncli_close(&client);

    return 0;
}
