#include "asyncServer.h"



AsyncServer::AsyncServer(MemQ *memQPtr)
{
	_memQPtr = memQPtr;
}

void AsyncServer::setServerCbs(send_t send, ackWait_t ackFunc)
{
  _send = send;
  _ackWait = ackFunc;
}

void AsyncServer::setSchema(uint8_t payloadSize, uint8_t total)
{
  totalPayload = total;
  Serial.print(F("Pld Size: ")); Serial.println(payloadSize);
  // payloadBuf = (uint8_t*)malloc(payloadSize * totalPayload);
  payloadBuf = (uint8_t*)calloc(payloadSize * totalPayload,sizeof(uint8_t));
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
  bool ok = true;

  if(_send == NULL) ok = false;
  if(_ackWait == NULL) ok = false;
  if(_toJson == NULL ) ok = false;

  if(ok == true)
  {
  	Serial.println(F("Server Init ok"));
  }
  else
  {
  	Serial.println(F("Server init failed"));
  }
}

void AsyncServer::printPayload(byte *buf, byte len)
{
  for (byte i = 0; i < len; i++)
  {
    Serial.print(buf[i]); Serial.print(" ");
  }
  Serial.println();
}

void AsyncServer::sendLoop(bool connected)
{
  if (connected)
  {
    // Serial.println(F("Sending Data.."));
    int pipeAck;
    switch (sendState)
    {
      case READ_MEM:
        // Serial.println(F("S_STATE: READ_MEM"));
        this -> payloadPtr = (uint8_t*)_memQPtr -> read(payloadBuf, totalPayload);
        if (payloadPtr != NULL)
        {
          printPayload(payloadPtr,32);
          sendState = TO_JSON;
        }
        break;
      case TO_JSON:
        Serial.println(F("S_STATE: TO_JSON"));
        jsonPtr = _toJson(payloadPtr, jsonBuffer, totalPayload);
        Serial.println(jsonPtr);
        sendState = SERVER_SEND;
        break;
      case SERVER_SEND:
        Serial.println(F("S_STATE: SEND"));
        if (jsonPtr != NULL)
        {
          _send(jsonPtr);
          sendState = WAIT_ACK;
        }
        break;
      case WAIT_ACK:
        Serial.println(F("S_STATE: WAIT"));
        pipeAck = _ackWait();
        Serial.print(F("===> ACK : ")); Serial.println(pipeAck);
        if (pipeAck == 200)
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
        sendState = SERVER_SEND;
        break;
    }
  }
}
