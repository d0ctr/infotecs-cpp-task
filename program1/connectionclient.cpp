#include "connectionclient.hpp"

ConnectionClient::~ConnectionClient()
{
  if(started)
  {
    tryToSend("end");
  }
  close(server_socket);
}

bool ConnectionClient::isStarted()
{
  return started;
}

void ConnectionClient::tryToSend(const std::string &line)
{
  std::string tmp = line + '_';
  const char *line_c = tmp.c_str();
  int count;
  if((count = send(server_socket, line_c, strlen(line_c), 0)) < 0)
  {
    throw std::invalid_argument("Error sending to server.");
  }
}

void ConnectionClient::readyClientConnection()
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

    if(connect(server_socket, (struct sockaddr *)&server_socket_name, server_socket_name_size) < 0) 
    {
      throw std::invalid_argument("Can not connect to server socket.");
    }
    
    tryToSend("start");
    started = true;
  }
  catch(const std::exception_ptr e)
  {
    std::rethrow_exception(e);
  }
}
