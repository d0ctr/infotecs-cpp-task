#include "connectionhost.hpp"

ConnectionHost::~ConnectionHost()
{
  unlink(server_socket_name.sun_path);
  close(server_socket);
  close(client_socket);
}

std::string ConnectionHost::readFromSocket()
{
  read_stream = fdopen(client_socket, "r");
  std::string new_line("");
  char c;
  while((c = fgetc(read_stream)) != '_')
  {
    new_line += c;
  }
  return new_line;
}

void ConnectionHost::readyHostConnection()
{
  try
  {
    if((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
      throw std::invalid_argument("Server socket descriptor can not be generated.");
    }

    server_socket_name.sun_family = AF_UNIX;
    strcpy(server_socket_name.sun_path, NAME);
    server_socket_name_size = sizeof(server_socket_name.sun_family) + strlen(server_socket_name.sun_path);

    unlink(NAME);
    if(bind(server_socket, (const sockaddr *)&server_socket_name, server_socket_name_size) < 0)
    {
      throw std::invalid_argument("Cannot bind socket with name.");
    }
    
    if(listen(server_socket, 5) < 0)
    {
      throw std::invalid_argument("Failure on seting que for connections.");
    }

    if((client_socket = accept(server_socket, &client_socket_name, &client_socket_name_size)) < 0)
    {
      throw std::invalid_argument("Client socket descriptor can not be generated.");
    }

    if(readFromSocket() != "start")
    {
      throw std::invalid_argument("Wrong connection start.");
    }
  }
  catch(const std::exception_ptr &e)
  {
    std::rethrow_exception(e);
  }
}
