#include "outputprocessor.hpp"

OutputProcessor::OutputProcessor()
{
  exception_occured = false;
  cl = ConnectionClient();
}

OutputProcessor::OutputProcessor(const std::shared_ptr<std::mutex> &mutex_ptr)
{
  this->mutex_ptr = mutex_ptr;
  exception_occured = false;
  cl = ConnectionClient();
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

void OutputProcessor::setMutexPtr(const std::shared_ptr<std::mutex> &mutex_ptr)
{
  this->mutex_ptr = mutex_ptr;
}

std::shared_ptr<std::mutex> OutputProcessor::getMutexPtr()
{
  return mutex_ptr;
}

ConnectionClient OutputProcessor::getConectionClient()
{
  return cl;
}

bool OutputProcessor::isExceptionOccured()
{
  return exception_occured;
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
    cl.readyClientConnection();
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
        cl.tryToSend(std::to_string(getSum(line)));
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
    std::cerr << "Cannot not function without running program2." << std::endl;
    raise(SIGINT);
  }
  mutex_ptr->unlock();
}