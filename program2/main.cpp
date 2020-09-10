#include "connectionclient.hpp"

int main()
{
  try
  {
    ConnectionClient cc;
    cc.connectToServer();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return -1;
  }
  return 0;
}