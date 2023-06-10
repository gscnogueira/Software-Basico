#include <iostream>
#include <errors.hpp>

AssemblerError::AssemblerError(const std::string& mensagem, std::string error_type,int _line)
	: std::runtime_error(mensagem)
	, type(error_type)
	, cont_line(_line)
{}


void AssemblerError::print(std::string f_name, std::string line) const{
  std::cerr << "\e[1m"+ f_name+":\e[0m";
  std::cerr <<"linha "<< cont_line;
  std::cerr <<":\033[31mErro " + get_type() +"\033[0m: ";
  std::cerr <<  what() << std::endl;
  std::cerr << "\t" + line <<std::endl;
}


