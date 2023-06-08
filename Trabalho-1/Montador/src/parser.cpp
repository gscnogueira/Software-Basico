#include <parser.hpp>

std::set<std::string> validInstructionsOneOperand = {
    "ADD","SUB","INPUT","LOAD", "DIV", "MUL", "STORE","JMPP","JMPZ","JMPN","OUTPUT"
};

bool Line::is_instruction() const{
    auto text = cmd.text;
    auto it = INSTRUCTION_TABLE.find(text);
    return (it!=INSTRUCTION_TABLE.end());
}

bool Line::has_label_declaration() const{
    return label!="";
}

bool Line::is_directive() const{
    return DIRECTIVES_TABLE.count(cmd.text);
}

bool not_is_identifier_operand(Token token){
	return token.type != 0||token.text[token.text.size()-1] == ':';
}

void process_line(int i,int limit,std::vector<Token> tokens){
	if(tokens[i].type != 1){
	  throw AssemblerError("Erro na analise sintatica", "Sintático");
	}
	if(tokens[i].text == "SECTION"){
		// precisa ser seguido da palavra reservada DATA ou TEXT
		if(limit-i != 2||(tokens[i+1].text != "DATA"&&tokens[i+1].text != "TEXT")){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		}
	}
	else if(tokens[i].text == "EXTERN:"){
		// precisa ser seguido de um rotulo sem ser declaração
		if(limit-i != 2||not_is_identifier_operand(tokens[i+1])){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		}
	}
	else if(tokens[i].text == "PUBLIC"){
		// precisa ser seguido de rotulo
		if(limit-i != 2||not_is_identifier_operand(tokens[i+1])){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		}
	}
	else if(tokens[i].text == "SPACE"){
		// pode aceitar argumento
		if(limit-i > 2){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		} else{
			if(limit-i == 2&&tokens[i+1].type != 2){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
			}
		}
	}
	else if(tokens[i].text == "CONST"){
		// precisa ter uma constante depois
		if(limit-i != 2||tokens[i+1].type != 2){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		}
	}
	else if(tokens[i].text == "STOP"){
		// não pode ter nada depois dele
		if(limit-i != 1){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		}
	}
	else if(tokens[i].text == "COPY"){
		if(limit-i != 4||not_is_identifier_operand(tokens[i+1])||tokens[i+2].text != ","||not_is_identifier_operand(tokens[i+3])){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		}
	}
	else if(validInstructionsOneOperand.count(tokens[i].text)){
		// aqui eu agrupei as instruções que tem a sintaxe igual
		if(limit-i != 2||not_is_identifier_operand(tokens[i+1])){
		  throw AssemblerError("Erro na analise sintatica", "Sintático");
		}
	}
}

Line parse_line(std::string line){
  auto tokens = scan_line(line);
  int limit = tokens.size();
  int labels = 0;
  for(int i = 0;i < limit;++i){
    if(labels >= 2){
      throw AssemblerError("Erro na analise sintatica", "Sintático");
    }
    //pulando as labels das instruções
    if(tokens[i].text[tokens[i].text.size()-1] == ':'){
      ++labels;
      continue;
    }
    process_line(i,limit,tokens);
    break;
  }

  std::string label = tokens[0].type ==tokens[0].Identifier? tokens[0].text :  "";
  
  auto cmd = label == "" ? tokens[0] : tokens[1];

  std::vector<Token> args(tokens.begin()+1, tokens.end());

  return Line(label, cmd,args);
}
