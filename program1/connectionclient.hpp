#ifndef CONNECTIONCLIENT_HPP
#define CONNECTIONCLIENT_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <sys/un.h>
#include <string>
#include <sys/unistd.h>

class ConnectionClient
{
  public:
    ConnectionClient() = default;
    ConnectionClient(std::string socket_name);
    ~ConnectionClient();
    void generateSocketDescriptor();
    void connectToServer();
    void send();
  private:
    int server_socket;
    sockaddr_un server_socket_name;
    socklen_t server_socket_name_size;
};
#endif