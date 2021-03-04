
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../Utils.h"



int main (void)
{
    //  Prepare our context and publisher
    void *context = zmq_init(1);

    void *publisher = zmq_socket (context, ZMQ_PUB);
    zmq_bind (publisher, "tcp://127.0.0.1:3333");


    while (1) {
        //  Send message to all subscribers
        double temperature = pseudorand(30.0);
        char temp[7];
        sprintf(temp,"%f", temperature);

        zmq_msg_t message;
        zmq_msg_init_size (&message, strlen (temp));
        memcpy (zmq_msg_data (&message), temp, strlen (temp));
        zmq_msg_send (&message,publisher , 0);
        sleep(2);
        zmq_msg_close (&message);

    }

    zmq_close (publisher);
    zmq_term (context);
    return 0;
}
