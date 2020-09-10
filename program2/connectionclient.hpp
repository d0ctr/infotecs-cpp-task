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
#include <stdio.h>

#define NAME "/tmp/program1_program2"

class ConnectionClient
{
  public:
    ConnectionClient() = default;
    ~ConnectionClient();
    void connectToServer();
    void tryToSend(const std::string line);
  private:
    FILE *server_stream;
    int server_socket;
    struct sockaddr_un server_socket_name;
    socklen_t server_socket_name_size;
};
#endif