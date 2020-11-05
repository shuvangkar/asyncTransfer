#include "asyncServer.h"

const char temp[] = "This is just test";


void AsyncServer::setServerCbs(send_t send, ackWait_t ackFunc)
{
  _send = send;
  _ackWait = ackFunc; 
}

void AsyncServer::setSchema(uint8_t payloadSize, uint8_t total)
{
  Serial.print(F("Pld Size: "));Serial.println(payloadSize);
  payloadBuf = (uint8_t*)malloc(payloadSize*total);
  if(payloadBuf !=NULL)
  {
    Serial.println(F("Payload Memory allocated"));
  }
}

void AsyncServer::setJson(toJson_t tojson, uint16_t jsonBufSize)
{
  _toJson = tojson;
  jsonBuffer = (char*)malloc(jsonBufSize);
  if(payloadBuf !=NULL)
  {
    Serial.println(F("JSON Memory allocated"));
  }
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
//        _memQPtr -> read();

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
