#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main(void) {
    //  Socket to talk to clients
    void *context = zmq_ctx_new();

    void *responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:5555");

    assert (rc == 0);

    while (1) {
        char buffer[10];

        zmq_recv(responder, buffer, 10, 0);
        int index=0;

        for(int i=0; i<strlen(buffer); i++){
            if(buffer[i]=='\0'){
                index=i+1;
            }
        }
        char buffer_reply[index];
        strcpy(buffer_reply, buffer);
        printf("message received : %s\n", buffer_reply);
        sleep(1);          //  Do some 'work'
        zmq_send(responder, buffer_reply, index, 0);
    }
    return 0;
}