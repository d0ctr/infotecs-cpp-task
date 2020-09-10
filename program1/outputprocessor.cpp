#include "outputprocessor.hpp"

OutputProcessor::OutputProcessor()
{
  exception_occured = false;
}

OutputProcessor::OutputProcessor(std::shared_ptr<std::mutex> &mutex_ptr)
{
  this->mutex_ptr = mutex_ptr;
  exception_occured = false;
}

OutputProcessor::OutputProcessor(std::shared_ptr<std::mutex> &mutex_ptr, std::string socket_name)
{
  this->mutex_ptr = mutex_ptr;
  socket_name += "1";
  exception_occured = false;
  connection = ConnectionHost();
}

OutputProcessor::~OutputProcessor()
{
  if(mutex_ptr)
  {
    mutex_ptr->unlock();
  }
}

int OutputProcessor::getSum(const std::string &line)
{
  int sum = 0;
  for(char a : line)
  {
    if(isdigit(a))
    {
      sum += a - '0';
    }
  }
  return sum;
}

void OutputProcessor::setMutexPtr(std::shared_ptr<std::mutex> &mutex_ptr)
{
  this->mutex_ptr = mutex_ptr;
}

std::shared_ptr<std::mutex> OutputProcessor::getMutexPtr()
{
  return mutex_ptr;
}

std::string OutputProcessor::readFromBuffer()
{
  std::ifstream buf("buf", std::ios_base::in);
  std::string line;
  if(buf.is_open())
  {
    buf >> line;
  }
  else
  {
    throw std::invalid_argument("Error reading buffer.");
  }
  buf.close();
  if(std::remove("buf") != 0)
  {
    throw std::invalid_argument("Error deleting file.");
  }
  return line;
}

void OutputProcessor::start()
{
  try
  {
    connection.hostServer();
    while(true)
    {
      try
      {
        if(!exception_occured)
        {
          mutex_ptr->lock();
        }
        exception_occured = false;

        std::string line = readFromBuffer();
        std::cout << "Read from buffer: " << line << std::endl;
        
        mutex_ptr->unlock();
        std::this_thread::yield();
      }
      catch(std::exception &e)
      {
        if(std::cin.eof())
        {
          break;
        }
        std::cerr << e.what() << '\n';
        exception_occured = true;
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  mutex_ptr->unlock();
}