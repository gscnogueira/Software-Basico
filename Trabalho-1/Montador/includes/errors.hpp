#pragma once

#include <stdexcept>
#include <string>

class AssemblerError : public std::runtime_error{
public:
  AssemblerError(const std::string& mensagem, std::string error_type,int _line);
  inline std::string get_type() const
  {
    return type;
  }

  void print(std::string f_name, std::string line) const;
private:
	std::string type;
	int cont_line;
};
