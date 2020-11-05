#include "asyncServer.h"

void AsyncServer::setCb(send_t send, waitForAck_t ackFunc)
{
  _send = send;
  _waitForAck = ackFunc;
}
