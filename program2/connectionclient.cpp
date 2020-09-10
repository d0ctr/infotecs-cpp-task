#include "connectionclient.hpp"

ConnectionClient::~ConnectionClient()
{
  close(server_socket);
}

void ConnectionClient::connectToServer()
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
    
    if(connect(server_socket, (sockaddr *)&server_socket_name, server_socket_name_size) < 0) 
    {
      throw std::invalid_argument("Can not connect to server socket.");
      return;
    }
    server_stream = fdopen(server_socket, "r");
    // char c;
    // std::string line("");
    // while((c = fgetc(server_stream)))
    // {
    //   line += c;
    // }
    // std::cout << line << std::endl;

    // send(server_socket, "client\0", 8, 0);
  }
  catch(const std::exception& e)
  {
    throw e;
  }
}