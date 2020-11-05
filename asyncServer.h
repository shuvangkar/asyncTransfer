#ifndef _ASYNC_SERVER_H
#define _ASYNC_SERVER_H
#include <Arduino.h>
#include "MemQ.h"

typedef void (*send_t)(const char* data);
typedef int (*waitForAck_t)(void);

class AsyncServer
{
  public:
    void setCb(send_t send, waitForAck_t ackFunc);
    void sendLoop(bool sendPermit);
  private:
    bool _sendNow
    MemQ *_memQPtr;
    send_t _send;
    waitForAck_t _waitForAck;

};
#endif
