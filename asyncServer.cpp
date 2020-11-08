#include "asyncServer.h"


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

void AsyncServer::start()
{
  sendState = READ_MEM;
}

void AsyncServer::sendLoop(bool connected)
{
  if (connected)
  {
    Serial.println(F("Sending Data.."));
    uint8_t *flashPtr = NULL;
    char *json = NULL;
    switch (sendState)
    {
      case READ_MEM:
        Serial.println(F("S_STATE: READ_MEM"));
        flashPtr = (uint8_t*)_memQPtr -> read(payloadBuf, totalPayload);
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
        sendState = SERVER_SEND;
        break;
      case SERVER_SEND:
        Serial.println(F("S_STATE: SEND"));
        if (json != NULL)
        {
          _send(json);
          sendState = WAIT_ACK;
        }
        break;
      case WAIT_ACK:
        Serial.println(F("S_STATE: WAIT"));
        if (_ackWait() == 200)
        {
          sendState = SEND_SUCCESS;
        }
        else
        {
          sendState = FAILED;
        }
        break;
      case SEND_SUCCESS:
        Serial.println(F("S_STATE: SUCCESS"));
        sendState = READ_MEM;
        break;
      case FAILED:
        Serial.println(F("S_STATE: FAILED"));
        break;
    }
  }
}
