#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <preprocessor.hpp>

int prePocessorFile(std::string file){
	std::string line;
	std::vector<std::string> Buffer;

	std::ifstream fin(file);
	if (!fin.is_open()) return 1;
	
	std::ofstream fout("bin_preprocessor.asm");
	if (!fout.is_open()) return 1;

	int qntdArgs = 0;

	while(std::getline(fin, line)){
        
		size_t posComment = line.find(';');
		if(posComment != std::string::npos)	
			line = line.substr(0,posComment);

		// transforma todos os caracteres da linha em maiusculo
		for(int i = 0; line[i] != '\0';++i)
			line[i] = (line[i] >= 'a' && line[i] <= 'z') ? line[i]-32 : line[i];
		
		// retirar o rotulo se tiver da linha para poder tratar somente a instrução
		size_t posRotulo = line.find(':');
		if (posRotulo != std::string::npos) {
			Buffer.push_back(line.substr(0, posRotulo+1));
			line = line.substr(posRotulo+1);
		}

		// trata os tipos de instruções e diretivas
		std::istringstream iss(line);
		std::string token;

		while(iss >> token){
			if(!qntdArgs){
				if(token == "COPY") qntdArgs = 3;
				else if(token == "STOP" || token == "SPACE") qntdArgs = 0;
				else qntdArgs = 1;
			}
			else qntdArgs--;
			Buffer.push_back(token);
			if(!qntdArgs){
				int limit = Buffer.size();
				for(int i = 0; i < limit;++i){
					fout << Buffer[i];
					if(i+1 < limit) fout.put(' ');
				}
				fout.put('\n');
				Buffer.clear();
			}
		}
	}
	fin.close();
	fout.close();
	return 0;
}
