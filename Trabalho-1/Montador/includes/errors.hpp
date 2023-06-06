#pragma once

#include <stdexcept>
#include <string>

class AssemblerError : public std::runtime_error{
public:
  AssemblerError(const std::string& mensagem, std::string error_type) : std::runtime_error(mensagem), type(error_type){}

  inline std::string get_type() const
  {
    return type;
  }

  void print(std::string f_name, unsigned int line) const;

private:
  std::string type;


};
