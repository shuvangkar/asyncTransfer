#ifndef _ASYNC_SERVER_H
#define _ASYNC_SERVER_H
#include <Arduino.h>
#include "MemQ.h"

typedef void (*send_t)(const char* data);
typedef int (*waitForAck_t)(void);

class AsyncServer
{
  public:
    void setCbFuncs(send_t send, waitForAck_t ackFunc);
    void sendLoop(bool sendPermit);
  private:
    MemQ *_memQPtr;
    send_t _send;
    waitForAck_t _waitForAck;
    uint8_t *_flashdataPtr;
    uint8_t *_payloadPtr;
    
    
};
#endif
