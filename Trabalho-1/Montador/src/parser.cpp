#include <parser.hpp>

std::set<std::string> validInstructionsOneOperand = {
    "ADD","SUB","INPUT","LOAD", "DIV", "MUL", "STORE","JMPP","JMPZ","JMPN","OUTPUT"
};

bool is_identifier_op(Token token){
	return token.type == 0||token.lexeme[token.lexeme.size()-1] != ':';
}

bool assert_copy(int i,int limit,std::vector<Token> tokens){
	if(
	limit-i == 4&&is_identifier_op(tokens[i+1])&&
	tokens[i+2].lexeme == ","&&is_identifier_op(tokens[i+3])
	){
		return false;
	}
	else if(
		limit-i == 6&&((is_identifier_op(tokens[i+1])&&tokens[i+2].lexeme == "+"&&
		tokens[i+3].type == 2&&tokens[i+4].lexeme == ","&&is_identifier_op(tokens[i+5]))||
		(is_identifier_op(tokens[i+1])&&tokens[i+2].lexeme == ","&&is_identifier_op(tokens[i+3])&&
		tokens[i+4].lexeme == "+"&&tokens[i+5].type == 2))
	){
		return false;
	}
	else if(
		limit-i == 8&&is_identifier_op(tokens[i+1])&&tokens[i+2].lexeme == "+"&&
		tokens[i+3].type == 2&&tokens[i+4].lexeme == ","&&is_identifier_op(tokens[i+5])&&
		tokens[i+6].lexeme == "+"&&tokens[i+7].type == 2
	){
		return false;
	}
	return true;
}

bool assert_inst(int i,int limit,std::vector<Token> tokens){
	if(limit-i == 2&&is_identifier_op(tokens[i+1])){
		return false;
	}
	if(limit-i == 4&&is_identifier_op(tokens[i+1])&&tokens[i+2].lexeme == "+"&&tokens[i+3].type == 2){
		return false;
	}
	return true;
}

bool not_is_identifier_op(Token token){
	return token.type != 0||token.lexeme[token.lexeme.size()-1] == ':';
}

void process_line(int i,int limit,std::vector<Token> tokens){
	if(tokens[i].type != 1||tokens[i].lexeme == "+"){
	  throw AssemblerError("Começo invalido de instrução", "Sintático");
	}
	if(tokens[i].lexeme == "SECTION"){
		// precisa ser seguido da palavra reservada DATA ou TEXT
		if(limit-i != 2||(tokens[i+1].lexeme != "DATA"&&tokens[i+1].lexeme != "TEXT")){
		  throw AssemblerError("Erro na diretiva SECTION", "Sintático");
		}
	}
	else if(tokens[i].lexeme == "EXTERN:"){
		// precisa ser seguido de um rotulo sem ser declaração
		if(limit-i != 2||not_is_identifier_op(tokens[i+1])){
		  throw AssemblerError("Erro na diretiva EXTERN", "Sintático");
		}
	}
	else if(tokens[i].lexeme == "PUBLIC"){
		// precisa ser seguido de rotulo
		if(limit-i != 2||not_is_identifier_op(tokens[i+1])){
		  throw AssemblerError("Erro na diretiva PUBLIC", "Sintático");
		}
	}
	else if(tokens[i].lexeme == "SPACE"){
		// pode aceitar argumento
		if(limit-i > 2){
		  throw AssemblerError("Erro na quantidade de operadores da diretiva SPACE", "Sintático");
		} else if(limit-i == 2&&tokens[i+1].type != 2){
		  throw AssemblerError("Erro na constante da diretiva SPACE", "Sintático");
		}
	}
	else if(tokens[i].lexeme == "CONST"){
		// precisa ter uma constante depois
		if(limit-i != 2||tokens[i+1].type != 2){
		  throw AssemblerError("Erro na diretiva CONST", "Sintático");
		}
	}
	else if(tokens[i].lexeme == "STOP"){
		// não pode ter nada depois dele
		if(limit-i != 1){
		  throw AssemblerError("Erro na instrução stop", "Sintático");
		}
	}
	else if(tokens[i].lexeme == "COPY"){
		if(assert_copy(i,limit,tokens))
		{
		  throw AssemblerError("Erro nos operadores da instrução binaria", "Sintático");
		}
	}
	else if(validInstructionsOneOperand.count(tokens[i].lexeme)){
		// aqui eu agrupei as instruções que tem a sintaxe igual
		if(assert_inst(i,limit,tokens)){
		  throw AssemblerError("Erro nos operadores da instrução unaria", "Sintático");
		}
	}
}

Line parse_line(std::string line){
  auto tokens = scan_line(line);
  int limit = tokens.size();
  int labels = 0;
  for(int i = 0;i < limit;++i){
    if(labels >= 2){
      throw AssemblerError("Mais de uma label na linha", "Sintático");
    }
    //pulando as labels das instruções
    if(tokens[i].lexeme[tokens[i].lexeme.size()-1] == ':'){
      ++labels;
      continue;
    }
    process_line(i,limit,tokens);
    break;
  }
  return Line(tokens);
}
