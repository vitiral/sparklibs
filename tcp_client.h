#ifndef __tcp_client_h
#define __tcp_client_h

#include "allduino.h"

enum IO_STATUS{
    IO_FREE,
    IO_SENDING
};

class TCP_client{
private:
    TCPClient client;
    unsigned char state = IO_FREE;
    unsigned int last_ran;
    byte server[4];
    uint16_t port;
    char *endpoint;
    char *buffer;
    uint16_t buffer_len;
public:
    TCP_client();
    void init(byte ip_address[4], uint16_t port, char *endpoint);
    void set_buffer(char *buffer, uint16_t buf_len);
    uint16_t transmit_available();
    uint16_t transmit(char *message, uint16_t message_len);
    uint16_t transmit(char *buffer, uint16_t buf_len, char *message, uint16_t message_len);

};
#endif
