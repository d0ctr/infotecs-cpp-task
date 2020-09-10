#include "connectionhost.hpp"
#include <iostream>


#define SOCKETNAME "program1_program2"

int main()
{
  try
  {
    ConnectionHost ch(SOCKETNAME);
    ch.hostServer();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
}