#include <iostream>
#include <preprocessor.hpp>
#include <scanner.hpp>
#include <fstream>
#include <string>
#include <cstring>

int main(int argc, char** argv){

  std::ifstream input;
  std::string line;

  if(argc<2){
    std::cout<<"Número insuficiente de argumentos\n";
    return 1;
  }

  // prePocessorFile(argv[1]);

  input.open(strcat(argv[1],"_preprocessor.asm"));

  while(getline(input, line)){
    auto tokens = scan_line(line);
    for (auto e : tokens)
      std::cout<<e<<" | ";
    std::cout<<"\n";
  }

  return 0;
}
