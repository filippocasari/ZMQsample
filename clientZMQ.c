#include <zmq.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *itoa(int value, char *result, int base);

char *concat(const char *s1, const char *s2);


int main(void) {
    printf("Connecting to hello world server…\n");
    void *context = zmq_ctx_new();

    void *requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer[10];
        char *stringsent;
        char number;
        itoa(request_nbr, &number, 10);
        char *hello_string = "hello ";
        stringsent = concat(hello_string, &number);
        printf("Sending Hello %s…\n", stringsent);


        zmq_send(requester, stringsent, 9, 0);
        zmq_recv(requester, buffer, 10, 0);
        printf("Received World %s\n", buffer);

    }
    zmq_close(requester);
    //zmq_ctx_destroy (context);
    zmq_term(context);
    return 0;
}

char *itoa(int value, char *result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) {
        *result = '\0';
        return result;
    }

    char *ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 +
                                                                                           (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

char *concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
