#include <parser.hpp>

std::set<std::string> validInstructionsOneOperand = {
    "ADD","SUB","INPUT","LOAD", "DIV", "MUL", "STORE","JMPP","JMPZ","JMPN","OUTPUT"
};

bool is_identifier_op(Token token){
	return token.type == 0&&token.text[token.text.size()-1] != ':';
}

bool assert_copy(int i,int limit,std::vector<Token> tokens){
	if(
	limit-i == 4&&is_identifier_op(tokens[i+1])&&
	tokens[i+2].text == ","&&is_identifier_op(tokens[i+3])
	){
		return false;
	}
	else if(
		limit-i == 6&&((is_identifier_op(tokens[i+1])&&tokens[i+2].text == "+"&&
		tokens[i+3].type == 2&&tokens[i+4].text == ","&&is_identifier_op(tokens[i+5]))||
		(is_identifier_op(tokens[i+1])&&tokens[i+2].text == ","&&is_identifier_op(tokens[i+3])&&
		tokens[i+4].text == "+"&&tokens[i+5].type == 2))
	){
		return false;
	}
	else if(
		limit-i == 8&&is_identifier_op(tokens[i+1])&&tokens[i+2].text == "+"&&
		tokens[i+3].type == 2&&tokens[i+4].text == ","&&is_identifier_op(tokens[i+5])&&
		tokens[i+6].text == "+"&&tokens[i+7].type == 2
	){
		return false;
	}
	return true;
}

bool assert_inst(int i,int limit,std::vector<Token> tokens){
	if(limit-i == 2&&is_identifier_op(tokens[i+1])){
		return false;
	}
	if(limit-i == 4&&is_identifier_op(tokens[i+1])&&tokens[i+2].text == "+"&&tokens[i+3].type == 2){
		return false;
	}
	return true;
}

bool not_is_identifier_op(Token token){
	return token.type != 0||token.text[token.text.size()-1] == ':';
}

bool Line::is_instruction() const{
    auto text = cmd.text;
    auto it = INSTRUCTION_TABLE.find(text);
    return (it!=INSTRUCTION_TABLE.end());
}

bool Line::has_label_declaration() const{
    return label!="";
}

bool Line::is_data_directive() const{
    return DATA_DIRECTIVES_TABLE.count(cmd.text);
}
bool Line::is_section() const {
    return cmd.text == "SECTION";
}
bool Line::is_linking_directive() const {
    return cmd.text == "EXTERN:" || cmd.text == "PUBLIC";
};

bool not_is_identifier_operand(Token token){
	return token.type != 0||token.text[token.text.size()-1] == ':';
}

void process_line(int i,int limit,std::vector<Token> tokens){
	if(tokens[i].type != 1||tokens[i].text == "+"){
	  throw AssemblerError("Começo invalido de instrução", "Sintático");
	}
	if(tokens[i].text == "SECTION"){
		// precisa ser seguido da palavra reservada DATA ou TEXT
		if(limit-i != 2||(tokens[i+1].text != "DATA"&&tokens[i+1].text != "TEXT")){
		  throw AssemblerError("Erro na diretiva SECTION", "Sintático");
		}
	}
	else if(tokens[i].text == "EXTERN:"){
		// precisa ser seguido de um rotulo sem ser declaração
		if(limit-i != 2||not_is_identifier_op(tokens[i+1])){
		  throw AssemblerError("Erro na diretiva EXTERN", "Sintático");
		}
	}
	else if(tokens[i].text == "PUBLIC"){
		// precisa ser seguido de rotulo
		if(limit-i != 2||not_is_identifier_op(tokens[i+1])){
		  throw AssemblerError("Erro na diretiva PUBLIC", "Sintático");
		}
	}
	else if(tokens[i].text == "SPACE"){
		// pode aceitar argumento
		if(limit-i > 2){
		  throw AssemblerError("Erro na quantidade de operadores da diretiva SPACE", "Sintático");
		} else if(limit-i == 2&&(tokens[i+1].type != 2||std::stoi(tokens[i+1].text) <= 0)){
		  throw AssemblerError("Erro na constante da diretiva SPACE", "Sintático");
		}
	}
	else if(tokens[i].text == "CONST"){
		// precisa ter uma constante depois
		if(limit-i != 2||tokens[i+1].type != 2){
		  throw AssemblerError("Erro na diretiva CONST", "Sintático");
		}
	}
	else if(tokens[i].text == "STOP"){
		// não pode ter nada depois dele
		if(limit-i != 1){
		  throw AssemblerError("Erro na instrução stop", "Sintático");
		}
	}
	else if(tokens[i].text == "COPY"){
		if(assert_copy(i,limit,tokens))
		{
		  throw AssemblerError("Erro nos operadores da instrução binaria", "Sintático");
		}
	}
	else if(validInstructionsOneOperand.count(tokens[i].text)){
		// aqui eu agrupei as instruções que tem a sintaxe igual
		if(assert_inst(i,limit,tokens)){
		  throw AssemblerError("Erro nos operadores da instrução unaria", "Sintático");
		}
	}
}

Line parse_line(std::string line){
  auto tokens = scan_line(line);
  int limit = tokens.size();
  std::string label;
  int labels = 0;
  Token cmd;
  int i = 0;
  for(i = 0;i < limit;++i){
    if(labels >= 2){
      throw AssemblerError("Mais de uma label na linha", "Sintático");
    }
    //pulando as labels das instruções
    if(tokens[i].text[tokens[i].text.size()-1] == ':'&&!tokens[i].type){
      ++labels;
	  label = tokens[i].text;
	  label.pop_back();
      continue;
    }
	cmd = tokens[i];
    process_line(i,limit,tokens);
    break;
  }
	std::vector<Token> args(tokens.begin()+i+1, tokens.end());

  return Line(label,cmd,args);
}
