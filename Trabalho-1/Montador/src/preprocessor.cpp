#include <preprocessor.hpp>

void pre_processor_file(std::string file){
	std::string line;
	std::vector<std::string> Buffer;

	std::ifstream fin("exemplos/"+file+".asm");
	if (!fin.is_open()) throw std::runtime_error("Falha ao abrir o arquivo de entrada");
	
	std::ofstream fout(file+"_preprocessor.asm");
	if (!fout.is_open()) throw std::runtime_error("Falha ao abrir o arquivo de saída");
	
	while(std::getline(fin, line)){
        
		// retira os comentarios da linha
		size_t posComment = line.find(';');
		if(posComment != std::string::npos)	line = line.substr(0,posComment);

		// transforma todos os caracteres da linha em maiusculo
		for(int i = 0; line[i] != '\0';++i)
			line[i] = (line[i] >= 'a' && line[i] <= 'z') ? line[i]-32 : line[i];
		
		// retirar o rotulo se tiver da linha para poder tratar somente a instrução
		size_t posRotulo = line.find(':');
		if (posRotulo != std::string::npos) {
			fout << line.substr(0, posRotulo+1);
			fout.put(' ');
			line = line.substr(posRotulo+1);
		}

		std::istringstream iss(line);
		std::string token;

		while(iss >> token) Buffer.push_back(token);

		if(!Buffer.empty()){
			int limit = Buffer.size();
			for(int i = 0; i < limit;++i){
				if(Buffer[i][1] == 'X' && Buffer[i][0] == '0') Buffer[i][1] = 'x'; 
				fout << Buffer[i];
				if(i+1 < limit) fout.put(' ');
			}
			fout.put('\n');
			Buffer.clear();
		}
	}
	fin.close();
	fout.close();
}
