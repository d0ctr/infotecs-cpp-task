#ifndef CONNECTIONHOST_HPP
#define CONNECTIONHOST_HPP

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

class ConnectionHost
{
  public:
    ConnectionHost() = default;
    ~ConnectionHost();
    void hostServer();
  private:
    FILE *client_stream;
    int server_socket;
    int client_socket;
    struct sockaddr_un server_socket_name;
    struct sockaddr client_socket_name;
    socklen_t server_socket_name_size;
    socklen_t client_socket_name_size;
};
#endif