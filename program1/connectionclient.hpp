#ifndef CONNECTIONCLIENT_HPP
#define CONNECTIONCLIENT_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/un.h>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>
#include <csignal>

#define NAME "/tmp/program1_program2"

class ConnectionClient
{
  public:
    ConnectionClient() = default;
    ~ConnectionClient();
    void readyClientConnection();
    void tryToSend(const std::string &line);
    bool isStarted();
    
  private:
    bool started;
    int server_socket;
    struct sockaddr_un server_socket_name;
    socklen_t server_socket_name_size;
};
#endif