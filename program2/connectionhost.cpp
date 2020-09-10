#include "connectionhost.hpp"

ConnectionHost::ConnectionHost()
{
  server_socket_name.sun_family = AF_UNIX;
  strcpy(server_socket_name.sun_path, NAME);
  server_socket_name_size = sizeof(server_socket_name.sun_family) + strlen(server_socket_name.sun_path);
}

ConnectionHost::~ConnectionHost()
{
  unlink(server_socket_name.sun_path);
  close(client_socket);
}
void ConnectionHost::generateSocketDescriptor()
{
  if((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
  {
    throw std::invalid_argument("Server socket can not be generated.");
  }
  else
  {
    std::cout << "[Socket descriptor is generated]" << '\n';
  }
}

void ConnectionHost::bindSocketName()
{
  unlink(server_socket_name.sun_path);
  if(bind(server_socket, (sockaddr *)&server_socket_name, server_socket_name_size) < 0)
  {
    throw std::invalid_argument("Cannot bind socket with name.");
  }
  else
  {
    std::cout << "[Name successfully binded]" << '\n';
  }
}

void ConnectionHost::waitForClient()
{
  if(listen(server_socket, 5) < 0)
  {
    throw std::invalid_argument("Failure on client awaitting.");
  }
  else
  {
    std::cout << "[Client successfully hand-shaked]" << '\n';
  }
}

void ConnectionHost::hostServer()
{
  try
  {
    generateSocketDescriptor();
    bindSocketName();
    waitForClient();

    if((client_socket = accept(server_socket, &client_socket_name, &client_socket_name_size)) < 0)
    {
      throw std::invalid_argument("Client socket descriptor can not be generated.");
    }
    else
    {
      std::cout << "[Client socket descriptor is generated]" << '\n';
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return;
  }
}