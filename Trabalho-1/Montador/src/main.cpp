#include "preprocessor.hpp"
#include "parser.hpp"
#include "fstream"
#include "cstring"

int main(int argc, char** argv){
	std::ifstream input;
  	std::string line;
  	if(argc < 2){
    	std::cout<<"Número insuficiente de argumentos\n";
    	exit(1);
  	}

	try{
		pre_processor_file(argv[1]);
		input.open(strcat(argv[1],"_preprocessor.asm"));
	} catch(const std::runtime_error& e){
		std::cout << e.what() << std::endl;
		exit(1);
	}

	int cont_line = 0;

  	while(getline(input, line)){
    	try{
			std::cout << cont_line << "\n";
			cont_line++;
			parse_line(line);
		} catch (const SintaxErro& e){
			std::cout << e.what() << "\n";
		}
	}	
	return 0;
}
