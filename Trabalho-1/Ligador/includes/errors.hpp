#pragma once

#include <stdexcept>
#include <string>
#include <sstream>

class LinkerError : public std::runtime_error{
public:
  LinkerError(const std::string& mensagem) : std::runtime_error(mensagem){}

};
