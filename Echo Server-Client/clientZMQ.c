#include <zmq.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../Utils.h"


int main(void) {
    printf("Connecting to Echo Server…\n");
    void *context = zmq_ctx_new();

    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://127.0.0.1:5555");
    char *hello_string = "hello ";
    char number;
    char *stringsent;
    int count = 0;
    int a = 0;


    for (; count < 10; count++) {


        itoa(a, &number, 10);




        stringsent = concat(hello_string, &number);

        printf("Sending Hello %s…\n", stringsent);

        unsigned long time_sending = (unsigned long) time(NULL);

        zmq_send(requester, stringsent, 8, 0);
        zmq_recv(requester, stringsent, strlen(stringsent), 0);

        unsigned long time_receiving = (unsigned long) time(NULL);

        unsigned long rtt = time_receiving - time_sending;

        printf("Echo Received :%s\n", stringsent);
        printf("RTT: %lu\t seconds\n", rtt);
        a++;


    }

    zmq_close(requester);
    zmq_term(context);
    return 0;
}

