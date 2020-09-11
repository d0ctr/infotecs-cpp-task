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
#include <csignal>

#include "connectionclient.hpp"

class OutputProcessor
{
  public:
    OutputProcessor();
    OutputProcessor(const std::shared_ptr<std::mutex> &mutex_ptr);
    ~OutputProcessor();

    std::shared_ptr<std::mutex> getMutexPtr();
    void setMutexPtr(const std::shared_ptr<std::mutex> &mutex_ptr);
    
    ConnectionClient getConectionClient();
    bool isExceptionOccured();  
    std::string readFromBuffer();
    int getSum(const std::string &line);
    void start();
  private:
    bool exception_occured;
    std::shared_ptr<std::mutex> mutex_ptr;
    ConnectionClient cl;
};
#endif