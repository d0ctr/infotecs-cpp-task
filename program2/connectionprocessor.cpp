#include "connectionprocessor.hpp"

ConnectionProcessor::ConnectionProcessor()
{
  ch = ConnectionHost();
}

ConnectionHost ConnectionProcessor::getConnectionHost()
{
  return ch;
}

void ConnectionProcessor::start()
{
  try
  {
    ch.readyHostConnection();
    std::string new_line;
    while((new_line = ch.readFromSocket()) != "end")
    {
      try
      {
        if(new_line.length() > 2)
        {
          int value = std::stoi(new_line);
          if(value % 32 == 0)
          {
            std::cout << value << std::endl;
          }
          else
          {
            throw std::invalid_argument("The value is not a multiple of 32.");
          }
        }
        else
        {
          throw std::invalid_argument("The value is not more than 2 digits long.");
        }
      }
      catch(const std::exception &e)
      {
        std::cerr << e.what() << std::endl;
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  
}