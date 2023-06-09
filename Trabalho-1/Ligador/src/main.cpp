#include <iostream>
#include <linker.hpp>



int main(int argc, char** argv){

  try {

    if(argc < 2)
      throw LinkerError("Nenhum arquivo de entrada foi fornecido");

    std::vector<Module> modules;

    for (int i=1; i < argc; i++)
      modules.push_back(Module(argv[i]));

    auto gdt = gen_global_definition_table(modules);

    Module main = modules[0];

    for (int i = 1; i < argc-1; i++){
        main = link(main, modules[i], gdt);
    }

    main.write_exec();

  }
  catch(const LinkerError& e) {

    std::cerr <<"\033[31mErro:\033[0m "<<  e.what() <<std::endl;
    return 1;

  }
  return 0;
}

