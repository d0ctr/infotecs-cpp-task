#ifndef CONNECTIONHOST_HPP
#define CONNECTIONHOST_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

class ConnectionHost
{
  public:
    ConnectionHost(int domain, int type, int protocol);
  private:
    int domain;
    int type;
    int protocol;
    int sockfd;
};
#endif