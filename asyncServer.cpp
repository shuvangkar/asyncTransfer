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
char jsonBuffer[256];

const char temp[] = "This is just test";
void AsyncServer::setServerCbs(send_t send, waitForAck_t ackFunc)
{
  _send = send;
  _waitForAck = ackFunc;
}

void AsyncServer::setSchema(uint8_t payloadSz,toJson_t tojson, uint8_t total = 1)
{
  
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
