#include <scanner.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

void Scanner::scan(std::string f_name){
	std::ifstream input(f_name);
	std::string content;
	std::cout<<"rapaaaaz"<<std::endl;
	if(input.is_open()){
		while(std::getline(input, content)){
			std::cout<<content.size()<<" "+ content<<std::endl;
		}
	}
	else {
		std::cout<<"Falha ao abrir o arquivo"<<std::endl;
	}
}

std::string Scanner::pop(int n){
	std::cout<<"rapaaaaz"<<std::endl;
}

std::vector<std::string> scan_line(std::string line){

	std::string token;
	std::vector<std::string> tokens;
	std::stringstream ss(line);

	while(ss>>token)
		tokens.push_back(token);

	// analisar tokens
	// verificar se o primeiro é um rótulo 
	// Analisar os outros tokens

	return tokens;
}


