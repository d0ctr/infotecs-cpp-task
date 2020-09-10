#include "connectionhost.hpp"

ConnectionHost::~ConnectionHost()
{
  unlink(server_socket_name.sun_path);
  close(client_socket);
  close(server_socket);
}

void ConnectionHost::hostServer()
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
    if(bind(server_socket, (sockaddr *)&server_socket_name, server_socket_name_size) < 0)
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
    // send(client_socket, "server\0", 8, 0);

    client_stream = fdopen(client_socket, "r");
    // char c;
    // std::string line("");
    // while((c = fgetc(client_stream)))
    // {
    //   line += c;
    // }
    // std::cout << line << std::endl;
  }
  catch(const std::exception& e)
  {
    throw e;
  }
}