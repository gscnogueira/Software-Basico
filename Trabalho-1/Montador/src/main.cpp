#include <preprocessor.hpp>
#include <parser.hpp>
#include <fstream>
#include <code_generator.hpp>

int main(int argc, char** argv){

    std::ifstream input;
    std::string line;
    std::string file_name;
    unsigned int cont_line = 0;

    try{

        if(argc < 2)
            throw std::invalid_argument("Número insuficiente de argumentos");

        if(argc > 5)
            throw std::invalid_argument("Número de argumentos excede o limite");

        for (int i = 1; i<argc; i++){
            file_name = argv[i];
            Program prog(file_name);
            cont_line = 1;
            pre_processor_file(argv[1]);
            input.open(file_name + "_preprocessor.asm");
            while(getline(input, line)){
                std::cout << cont_line <<" " +  line<< std::endl;
                cont_line++;
                Line parsed_line = parse_line(line);
                prog.gen_code(parsed_line);
            }
        }
    }	

    catch (const AssemblerError& e){
        e.print(file_name, cont_line);
        return 1;
    }
    catch(const std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch(const std::invalid_argument& e){
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
