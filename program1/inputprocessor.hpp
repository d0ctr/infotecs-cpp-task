#ifndef INPUTPROCESSOR_HPP
#define INPUTPROCESSOR_HPP

#include <fstream>
#include <mutex>
#include <string>
#include <ctype.h>
#include <iostream>
#include <exception>
#include <memory>
#include <cstdlib>
#include <algorithm>
#include <thread>

class InputProcessor
{
  public:
    InputProcessor();
    InputProcessor(std::shared_ptr<std::mutex> &input_ptr);
    ~InputProcessor();
    void setMutexPtr(std::shared_ptr<std::mutex> &mutex_ptr);
    std::shared_ptr<std::mutex> getMutexPtr();
    void start();
  private:
    bool containesEvenNumbers(const std::string &line);
    std::string readInput();
    bool followsRequirements(const std::string &line);
    std::string reformatLine(std::string &line);
    void writeToBuffer(const std::string &line);

    std::shared_ptr<std::mutex> mutex_ptr;
    bool exception_occured;
};
#endif