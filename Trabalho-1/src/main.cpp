#include <iostream>
#include <fstream>
#include <preprocessor.hpp>

int apply_preproc_to_file(std::string asm_file);
int apply_lexer_to_file(char* asm_file); 
int apply_parser_to_file(char* asm_file);
int gen_code(char* asm_file); // não sei se o argumento deve ser um arquivo mesmo


int main(int argc, char** argv){

  apply_preproc_to_file(argv[1]);

  return 0;
}

int apply_preproc_to_file(std::string asm_file){

  std::ifstream file(asm_file);
  std::string content;

  while(file){
    std::getline(file, content);
    std::cout << content<< std::endl;
  }
  remove_white_spaces("ronaldo");

  return 0;
}
