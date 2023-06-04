#include <iostream>
#include <linker.hpp>



int main(int argc, char** argv){

  try {

    if(argc < 2)
      throw LinkerError("Nenhum arquivo de entrada foi fornecido");

    Module main(argv[1]);

    for (int i=2; i < argc; i++){
      Module aux(argv[i]);
      main = link(main, aux);
    }

    main.write_exec();

  }
  catch(const LinkerError& e) {

    std::cerr <<"\033[31mErro:\033[0m "<<  e.what() <<std::endl;
    return 1;

  }
  return 0;
}

