
#include "tcp_client.h"
TCP_Client::TCP_client(){
}

void TCP_Client::init(byte rest_ip[4], uint16_t rest_port, char *rest_endpoint){
    memcpy(server, rest_ip, 4);
    port = rest_port;
    endpoint = rest_endpoint;
    buffer = NULL;
    buf_len = 0;
}

void TCP_Client::set_buffer(char *buf, uint16_t len){
    buffer = buf;
    buf_len = len;
}

#define MIN_COM_PERIOD 80
uint16_t TCP_Client::transmit_available(){
    if(state == IO_SENDING){
        if(client.connected() == false){
            // we are done sending last message
            state = IO_FREE;
        }
        else{
            if(TIME_SINCE(last_ran) > MIN_COM_PERIOD) return true;
            return false;
        }
    }
    if(state == IO_FREE){
        if(client.connected()){
            return true;
        }
        return client.connect(server, port);
    }
    return false;
}

/* Transmit for if you set the buffer.
 * data should be a character array that is in JSON form
 **/
uint16_t TCP_Client::transmit(char *message, uint16_t message_len){
    transmit(buffer, buffer_len, message, message_len);
}

/**
 * Transmit data if you haven't or don't want to set the buffer.
 * Send the pointer to the buffer and the remaining length for the
 * first two variables. The rest is the same as above.
 **/
uint16_t TCP_Client::transmit(char *big_buf, uint16_t big_buf_len,
        char *message, uint16_t message_len){
    char small_buf[10];
    char *place = big_buf;
    uint16_t sbuf_len= big_buf_len;

    if(big_buf == NULL){
        return -1;
    }

    if(not manage_connection(cl)){
        return false;
    }
    sbuf_len = bstrncpy(&place, "POST ", sbuf_len);
    sbuf_len  = bstrncpy(&place, endpoint, sbuf_len);
    sbuf_len = bstrncpy(&place, " HTTP/1.1\r\nHost: ", sbuf_len);
    sbuf_len = bstrncpy(&place, server_str, sbuf_len);
    sbuf_len = bstrncpy(&place, "\r\nContent-Length: ", sbuf_len);
    itoa(len, small_buf, 10);
    sbuf_len = bstrncpy(&place, small_buf, sbuf_len);
    sbuf_len = bstrncpy(&place, "\r\nContent-Type: application/json\r\n", sbuf_len);
    sbuf_len = bstrncpy(&place, "Connection: keep-alive\r\n", sbuf_len);
    sbuf_len = bstrncpy(&place, "\r\n", sbuf_len);
    sbuf_len = bstrncpy(&place, message, sbuf_len);
    sbuf_len = bstrncpy(&place, "\r\n", sbuf_len);

    if(sbuf_len == 0){
        //Serial.println("BUF_LEN not enough!");
        return -1;
    }

    /*start = micros();*/
    client.write((const uint8_t *)big_buf, big_buf_len - sbuf_len); // Believe it or not -- this won't work for client.print!!!
    /*start = micros() - start;*/
    /*if(start > 600){*/
        /*Serial.println(start);*/
    /*}*/

    last_ran = millis();
    state = IO_SENDING;
    return true;
}

