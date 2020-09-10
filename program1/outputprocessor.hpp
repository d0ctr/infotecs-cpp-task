#ifndef OUTPUTPROCESSOR_HPP
#define OUTPUTPROCESSOR_HPP

#include <memory>
#include <mutex>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include "connectionclient.hpp"

class OutputProcessor
{
  public:
    OutputProcessor();
    OutputProcessor(std::shared_ptr<std::mutex> &mutex_ptr);
    OutputProcessor(std::shared_ptr<std::mutex> &mutex_ptr, std::string socket_name);
    ~OutputProcessor();
    void setMutexPtr(std::shared_ptr<std::mutex> &mutex_ptr);
    std::shared_ptr<std::mutex> getMutexPtr();
    int getSum(const std::string &line);
    void start();
  private:
    std::string readFromBuffer();
    bool exception_occured;
    std::shared_ptr<std::mutex> mutex_ptr;
    ConnectionClient conn;
};
#endif