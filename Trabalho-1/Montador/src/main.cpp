#include <preprocessor.hpp>
#include <parser.hpp>
#include <fstream>
#include <code_generator.hpp>

int Line::cont_line = 1;

int main(int argc, char** argv){

    std::string line;
    std::string file_name;

    try{

        if(argc < 2)
            throw std::invalid_argument("Número insuficiente de argumentos");

        if(argc > 5)
            throw std::invalid_argument("Número de argumentos excede o limite");

        for (int i = 1; i<argc; i++){
            file_name = argv[i];
            Program prog(file_name);

            pre_processor_file(file_name);

            std::ifstream input(file_name + "_preprocessor.asm");

            while(getline(input, line)){
                Line parsed_line = parse_line(line);
                prog.gen_code(parsed_line);
                Line::cont_line++;
            }

            prog.check_status();
            prog.write();
        }
    }	

    catch (const AssemblerError& e){
        e.print(file_name,line);
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
