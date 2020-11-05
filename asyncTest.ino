#include "asyncServer.h"
#include "payloadSchema.h"


void sendSerial(const char *data);
int wait();

AsyncServer server;
String rcvStr;

bool permitFlag;
void setup() 
{
  Serial.begin(9600);
  server.setServerCbs(sendSerial,wait);
  server.setSchema(sizeof(sensor_t),1);
  server.setJson(toJson,256);
  rcvStr.reserve(32);
  permitFlag = true;
  Serial.println(F("Setup done"));
}

void loop() 
{
//  server.sendLoop(permitFlag);
}

void sendSerial(const char *data)
{
  Serial.println(data);
}
int wait()
{
  if(Serial.available())
  {
    rcvStr = Serial.readString();
    int retData = rcvStr.toInt();
    Serial.print(F("ACK Received: "));Serial.println(retData);
  }
}
