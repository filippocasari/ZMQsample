
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <assert.h>


int main (int argc, char *argv [])
{
    int rc;
    void *context = zmq_init(1);

    //  Socket to talk to server
    printf ("Collecting updates from server...\n");
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    //127.0.0.1, 192.168.0.113
    rc = zmq_connect (subscriber, "tcp://192.168.0.113:3333");
    zmq_setsockopt( subscriber, ZMQ_SUBSCRIBE, "", 0 );
    assert (rc == 0);

    while(1){

        // Receive message from server
        zmq_msg_t message;
        zmq_msg_init (&message);

        zmq_msg_recv(&message, subscriber, 0);
        int size = zmq_msg_size (&message);
        char *string = malloc (size + 1);
        memcpy (string, zmq_msg_data (&message), size);
        zmq_msg_close (&message);
        string [size] = 0;
        printf("Temperature is: %s Cel\n",string);

    }

    zmq_close (subscriber);
    zmq_term (context);
    return 0;
}
