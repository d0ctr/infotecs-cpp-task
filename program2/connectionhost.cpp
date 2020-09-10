#include "connectionhost.hpp"

ConnectionHost::ConnectionHost(std::string socket_name)
{
  server_socket_name.sun_family = AF_UNIX;
  strcpy(server_socket_name.sun_path, socket_name.c_str());
  server_socket_name_size = sizeof(server_socket_name.sun_family) + strlen(server_socket_name.sun_path);
}

ConnectionHost::~ConnectionHost()
{
  unlink(server_socket_name.sun_path);
  close(client_socket);
}
void ConnectionHost::generateSocketDescriptor()
{
  if((server_socket = socket(server_socket_name.sun_family, SOCK_STREAM, 0)) < 0)
  {
    throw std::invalid_argument("Socket cannot be established with current settings.");
  }
  else
  {
    std::cout << "[Socket successfully estblished]" << '\n';
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
      throw std::invalid_argument("Cannot establish connection with client.");
    }
    else
    {
      std::cout << "[Connection successfully established]" << '\n';
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return;
  }
}