#include "connectionclient.hpp"

ConnectionClient::ConnectionClient(std::string socket_name)
{
  server_socket_name.sun_family = AF_UNIX;
  strcpy(server_socket_name.sun_path, socket_name.c_str());
  server_socket_name_size = sizeof(server_socket_name.sun_family) + strlen(server_socket_name.sun_path);
}

ConnectionClient::~ConnectionClient()
{
  close(server_socket);
}

void ConnectionClient::generateSocketDescriptor()
{
  if((server_socket = socket(server_socket_name.sun_family, SOCK_STREAM, 0)) < 0)
  {
    throw std::invalid_argument("Server socket can");
  }
  else
  {
    std::cout << "[Socket successfully estblished]" << '\n';
  }
}

void ConnectionClient::connectToServer()
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