#include "inputprocessor.hpp"

InputProcessor::InputProcessor()
{
  
  exception_occured = false;
}

InputProcessor::InputProcessor(std::shared_ptr<std::mutex> &mutex_ptr)
{
  this->mutex_ptr = mutex_ptr;
  exception_occured = false;
}

InputProcessor::~InputProcessor()
{
  if(mutex_ptr)
  {
    mutex_ptr->unlock();
  }
}

void InputProcessor::setMutexPtr(std::shared_ptr<std::mutex> &mutex_ptr)
{
  this->mutex_ptr = mutex_ptr;
}

std::shared_ptr<std::mutex> InputProcessor::getMutexPtr()
{
  return mutex_ptr;
}

bool InputProcessor::isExceptionOccured()
{
  return exception_occured;
}

std::string InputProcessor::reformatLine(std::string &line)
{
  std::sort(line.begin(), line.end(), std::greater<char>());
  std::string newline = "";
  for(char a : line)
  {
    if(((int)a - '0') % 2 == 0)
    {
      newline += "KB";
    }
    else
    {
      newline += a;
    }
  }
  return newline;
}

bool InputProcessor::followsRequirements(const std::string &line)
{
  for(char a : line)
  {
    if(!isdigit(a))
    {
      throw std::invalid_argument("Input must not contain non-digit symbols.");
    }
  }
  if(line.length() > 64)
  {
    throw std::invalid_argument("Input line is too long.");
  }
  return true;
}

std::string InputProcessor::readInput()
{
  std::string newline;
  std::cout << "> ";
  std::cin >> newline;
  if(std::cin.eof())
  {
    throw std::invalid_argument("EOF has been received, application will end itself now.");
  }
  return newline;
}

void InputProcessor::writeToBuffer(const std::string &line)
{
  std::ofstream buf("buf", std::ios_base::out);
  if(buf.is_open())
  {
    buf << line;
  }
  else
  {
    throw std::ios_base::failure("Error opening buffer file.");
  }
  buf.close();
}



void InputProcessor::start()
{
  while(true)
  {
    try
    {
      if(!exception_occured)
      {
        mutex_ptr->lock();
      }
      exception_occured = false;
      std::string newline = readInput();
      if(followsRequirements(newline))
      {
        std::string formatted_line = reformatLine(newline);
        writeToBuffer(formatted_line);
      }
      else
      {
        throw std::invalid_argument("Input line does not follow requirements.");
      }
      mutex_ptr->unlock();
      std::this_thread::yield();
      
    }
    catch(std::exception &e)
    {
      std::cerr << e.what() << '\n';
      exception_occured = true;
      if(std::cin.eof())
      {
        break;
      }
    }
  }
  mutex_ptr->unlock();
}