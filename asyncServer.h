#ifndef _ASYNC_SERVER_H
#define _ASYNC_SERVER_H
#include <Arduino.h>
#include "MemQ.h"

typedef void (*send_t)(const char*);
typedef int (*ackWait_t)(void);
typedef char *(*toJson_t)(uint8_t*, char*, uint8_t); //payload, json buffer, total

typedef enum state_e
{
  READ_MEM,
  TO_JSON,
  SERVER_SEND,
  WAIT_ACK,
  SEND_SUCCESS,
  FAILED,
};



class AsyncServer
{
  public:
  	AsyncServer(MemQ *memQPtr);
    void setServerCbs(send_t send, ackWait_t ackFunc);
    void setSchema(uint8_t payloadSize, uint8_t total = 1);
    void setJson(toJson_t tojson, uint16_t jsonBufSize = 128);
    void start();
    void sendLoop(bool connected);
  private:
    MemQ *_memQPtr;
    state_e sendState;

    send_t _send;
    ackWait_t _ackWait;
    toJson_t _toJson;

    uint8_t *payloadBuf = NULL;
    char *jsonBuffer = NULL;
    uint8_t totalPayload;

    uint8_t *payloadPtr = NULL;
};
#endif
