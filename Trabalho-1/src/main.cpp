#include <iostream>
#include <fstream>
#include <preprocessor.hpp>

//int apply_lexer_to_file(char* asm_file); 
//int apply_parser_to_file(char* asm_file);
//int gen_code(char* asm_file); // não sei se o argumento deve ser um arquivo mesmo


int main(int argc, char** argv){

  prePocessorFile(argv[1]);

  return 0;
}
