#include <zmq.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Utils.h"


int main(void) {
    printf("Connecting to hello world server…\n");
    void *context = zmq_ctx_new();

    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://127.0.0.1:5555");
    char *hello_string = "hello ";
    char number;
    char *stringsent;
    int count=0;
    int a=0;


    for (;count < 10; count++) {


        itoa(a, &number, 10);


        char buffer2[5];

        stringsent = concat(hello_string, &number);

        printf("Sending Hello %s…\n", stringsent);

        unsigned long time_sending=(unsigned long)time(NULL);

        zmq_send(requester, stringsent, 8, 0);
        zmq_recv(requester, buffer2, 6, 0);

        unsigned long time_receiving=(unsigned long)time(NULL);

        unsigned long rtt=time_receiving-time_sending;

        printf("Received :%s\n", buffer2);
        printf("RTT: %lu\t seconds\n", rtt);
        a++;



    }
    zmq_close(requester);
    //zmq_ctx_destroy (context);
    zmq_term(context);
    return 0;
}

