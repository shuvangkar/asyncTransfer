#include "asyncServer.h"

const char temp[] = "This is just test";


void AsyncServer::setServerCbs(send_t send, ackWait_t ackFunc)
{
  _send = send;
  _ackWait = ackFunc;
}

void AsyncServer::setSchema(uint8_t payloadSize, uint8_t total)
{
  totalPayload = total;
  Serial.print(F("Pld Size: ")); Serial.println(payloadSize);
  payloadBuf = (uint8_t*)malloc(payloadSize * totalPayload);
  if (payloadBuf != NULL)
  {
    Serial.println(F("Payload Memory allocated"));
  }
}

void AsyncServer::setJson(toJson_t tojson, uint16_t jsonBufSize)
{
  _toJson = tojson;
  jsonBuffer = (char*)malloc(jsonBufSize);
  if (payloadBuf != NULL)
  {
    Serial.println(F("JSON Memory allocated"));
  }
}

void AsyncServer::sendLoop(bool sendPermit)
{
  if (sendPermit)
  {
    Serial.println(F("Sending Data.."));
    uint8_t *flashPtr = NULL;
    char *json = NULL;
    switch (sendState)
    {
      case READ_MEM:
        flashPtr = _memQPtr -> read(payloadBuf, totalPayload);
        if (flashPtr != NULL)
        {
          payloadPtr = flashPtr;
          sendState = TO_JSON;
        }
        break;
      case TO_JSON:
        Serial.println(F("S_STATE: TO_JSON"));
        json = _toJson(payloadPtr, jsonBuffer, totalPayload);
        Serial.println(json);
        sendState = SEND;
        break;
      case SEND:
        if (json != NULL)
        {
          _send(json);
          sendState = WAIT;
        }
        break;
      case WAIT:
        if (_ackWait() == 200)
        {
          sendState = SUCCESS;
        }
        else
        {
          sendState = NO_CONNNECTION;
        }
        break;
      case SUCCESS:
        sendState = READ_MEM;
        break;
      case NO_CONNNECTION:
        break;
    }
  }
}
