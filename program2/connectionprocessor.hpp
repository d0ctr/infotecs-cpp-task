#include <iostream>
#include <string>
#include <exception>
#include <csignal>

#include "connectionhost.hpp"

class ConnectionProcessor
{
  public:
    ConnectionProcessor();
    ~ConnectionProcessor() = default;
    void start();
    ConnectionHost getConnectionHost();
    
  private:
    ConnectionHost ch;
};