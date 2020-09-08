#include "connectionhost.hpp"

ConnectionHost::ConnectionHost(int domain, int type, int protocol)
{
  this->domain = domain;
  this->type = type;
  this->protocol = protocol;
  sockfd = socket(domain, type, protocol);
  if(sockfd < 0)
  {
    throw std::invalid_argument("Socket cannot be established");
  }
  else
  {
    std::cout << "[Socket successfully estblished]" << std::endl;
  }
  
}