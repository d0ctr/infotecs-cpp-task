#include "connectionhost.hpp"
#include <iostream>

#define DOMAIN AF_LOCAL
#define TYPE SOCK_STREAM
#define PROTOCOL 0

int main()
{
  try
  {
    ConnectionHost ch(DOMAIN, TYPE, PROTOCOL);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
}