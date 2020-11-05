#ifndef _PAYLOAD_SCHEMA_H
#define _PAYLOAD_SCHEMA_H
#include <Arduino.h>

typedef struct sensor_t
{
  float current;
  float voltage;
};

typedef union payload_t
{
  sensor_t sensor;
};

char *toJson(uint8_t *payload, char *jsonBuf, uint8_t total = 1); 
#endif
