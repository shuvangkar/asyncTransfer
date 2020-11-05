#ifndef _ASYNC_SERVER_H
#define _ASYNC_SERVER_H
#include <Arduino.h>
#include "MemQ.h"

typedef void (*send_t)(const char*);
typedef int (*waitForAck_t)(void);
typedef char *(*toJson_t)(uint8_t*,char*, uint8_t);//payload, json buffer, total

class AsyncServer
{
  public:
    void setServerCbs(send_t send, waitForAck_t ackFunc);
    void setSchema(uint8_t payloadSz, uint8_t total = 1);
    void setJson(toJson_t tojson, uint16_t jsonBufsize = 128);
    void sendLoop(bool sendPermit);
  private:
    MemQ *_memQPtr;
    
    send_t _send;
    waitForAck_t _waitForAck;
    toJson_t _toJson;
    
    uint8_t _totalPayload;
    uint8_t *_flashdataPtr;
    uint8_t *_payloadPtr; 
};
#endif
