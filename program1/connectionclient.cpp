#include "connectionclient.hpp"

ConnectionClient::ConnectionClient()
{
  server_socket_name.sun_family = AF_UNIX;
  strcpy(server_socket_name.sun_path, NAME);
  server_socket_name_size = sizeof(server_socket_name.sun_family) + strlen(server_socket_name.sun_path);
}

ConnectionClient::~ConnectionClient()
{
  close(server_socket);
}

void ConnectionClient::generateSocketDescriptor()
{
  if((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    throw std::invalid_argument("Server socket descriptor can not be generated.");
  }
  else
  {
    std::cout << "[Server socket descriptor is generated]" << '\n';
  }
}

void ConnectionClient::connectToServer()
{
  try
  {
    generateSocketDescriptor();
    if (connect(server_socket, (sockaddr *)&server_socket_name, server_socket_name_size) < 0) 
    { 
      throw std::invalid_argument("Connection Failed"); 
    }
    else
    {
      std::cout << "[Server successfully hand-shaked]" << '\n';
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return;
  }
}