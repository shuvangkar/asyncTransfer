#include "asyncServer.h"

typedef enum state_e
{
  READ_MEM,
  TO_JSON,
  SEND,
  WAIT,
  SUCCESS,
  NO_CONNNECTION,
};
state_e sendState;

const char temp[] = "This is just test";
void AsyncServer::setCbFuncs(send_t send, waitForAck_t ackFunc)
{
  _send = send;
  _waitForAck = ackFunc;
}

void AsyncServer::sendLoop(bool sendPermit)
{
  if (sendPermit)
  {
    Serial.println(F("Sending Data.."));
    _send(temp);
    switch (sendState)
    {
        case READ_MEM:
        _memQPtr -> memQ.read();
        
        break;
        case TO_JSON:
        break;
        case SEND:
        break;
        case WAIT:
        break;
        case SUCCESS:
        break;
        case NO_CONNNECTION:
        break;
    }
  }
}
