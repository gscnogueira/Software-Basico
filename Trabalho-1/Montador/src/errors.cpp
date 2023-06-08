#include <iostream>
#include <errors.hpp>

void AssemblerError::print(std::string f_name, unsigned int line_number, std::string line) const{

  std::cerr << "\e[1m"+ f_name+":\e[0m";
  std::cerr <<"linha "<< line_number;
  std::cerr <<":\033[31mErro " + get_type() +"\033[0m: ";
  std::cerr <<  what() << std::endl;
  std::cerr << "\t" + line <<std::endl;
}


