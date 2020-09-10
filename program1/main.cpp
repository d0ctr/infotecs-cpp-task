#include <thread>

#include "inputprocessor.hpp"
#include "outputprocessor.hpp"

#define SOCKETNAME "program1_program2"
#define PROTOCOL 0
#define TYPE SOCK_STREAM
#define DOMAIN AF_LOCAL

int main()
{
  std::shared_ptr<std::mutex> mutex_ptr = std::make_shared<std::mutex>();
  std::shared_ptr<InputProcessor> inp = std::make_shared<InputProcessor>(mutex_ptr);
  std::shared_ptr<OutputProcessor> outp = std::make_shared<OutputProcessor>(mutex_ptr, SOCKETNAME);
  std::thread inp_t(&InputProcessor::start, inp);
  std::thread outp_t(&OutputProcessor::start, outp);
  inp_t.join();
  outp_t.join();
  return 0;
}