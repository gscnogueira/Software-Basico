#include <parser.hpp>
#include <lexererror.hpp>

std::set<std::string> validInstructionsOneOperand = {
    "ADD","SUB","INPUT","LOAD", "DIV", "MUL", "STORE","JMPP","JMPZ","JMPN","OUTPUT"
};

bool not_is_identifier_operand(Token token){
	return token.type != 0||token.lexeme[token.lexeme.size()-1] == ':';
}

void process_line(int i,int limit,std::vector<Token> tokens){
	if(tokens[i].type != 1){
		throw SintaxErro("Erro na analise sintatica");
	}
	if(tokens[i].lexeme == "SECTION"){
		// precisa ser seguido da palavra reservada DATA ou TEXT
		if(limit-i != 2||(tokens[i+1].lexeme != "DATA"&&tokens[i+1].lexeme != "TEXT")){
			throw SintaxErro("Erro na analise sintatica");
		}
	}
	else if(tokens[i].lexeme == "EXTERN:"){
		// precisa ser seguido de um rotulo sem ser declaração
		if(limit-i != 2||not_is_identifier_operand(tokens[i+1])){
			throw SintaxErro("Erro na analise sintatica");
		}
	}
	else if(tokens[i].lexeme == "PUBLIC"){
		// precisa ser seguido de rotulo
		if(limit-i != 2||not_is_identifier_operand(tokens[i+1])){
			throw SintaxErro("Erro na analise sintatica");
		}
	}
	else if(tokens[i].lexeme == "SPACE"){
		// pode aceitar argumento
		if(limit-i > 2){
			throw SintaxErro("Erro na analise sintatica");
		} else{
			if(limit-i == 2&&tokens[i+1].type != 2){
				throw SintaxErro("Erro na analise sintatica");
			}
		}
	}
	else if(tokens[i].lexeme == "CONST"){
		// precisa ter uma constante depois
		if(limit-i != 2||tokens[i+1].type != 2){
			throw SintaxErro("Erro na analise sintatica");
		}
	}
	else if(tokens[i].lexeme == "STOP"){
		// não pode ter nada depois dele
		if(limit-i != 1){
			throw SintaxErro("Erro na analise sintatica");
		}
	}
	else if(tokens[i].lexeme == "COPY"){
		// precisa ter um operando, um delimtiar e um operando
		if(limit-i != 4||not_is_identifier_operand(tokens[i+1])||tokens[i+2].type != 3||not_is_identifier_operand(tokens[i+3])){
			throw SintaxErro("Erro na analise sintatica");
		}
	}
	else if(validInstructionsOneOperand.count(tokens[i].lexeme)){
		// aqui eu agrupei as instruções que tem a sintaxe igual
		if(limit-i != 2||not_is_identifier_operand(tokens[i+1])){
			throw SintaxErro("Erro na analise sintatica");
		}
	}
}

void parse_line(std::string line){
    try{
		auto tokens = scan_line(line);
		int limit = tokens.size();
		int labels = 0;
		for(int i = 0;i < limit;++i){
			if(labels >= 2){
				throw SintaxErro("Erro na analise sintatica");
			}
			//pulando as labels das instruções
			if(tokens[i].lexeme[tokens[i].lexeme.size()-1] == ':'){
				++labels;
				continue;
			}
			process_line(i,limit,tokens);
			break;
		}
		
	} catch(const LexerErro& e){
		std::cout << e.what() << "\n";
	}
}