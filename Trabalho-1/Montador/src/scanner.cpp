#include "scanner.hpp"

std::set<std::string> validKeywords = {
    "COPY", "ADD","SECTION","SUB","SPACE","CONST","INPUT","+",
	"TEXT","LOAD","DIV","MUL","STORE","STOP","JMPP","JMPZ",
	"JMPN","DATA","EXTERN:","PUBLIC","OUTPUT","BEGIN","END"
};


bool process_elem_id(int cont,char element){
	if(cont == 0){
		return (element >= 'A' && element <= 'Z')||element == '_';
	} else{
		return (element >= 'A' && element <= 'Z')||element == '_'||(element >= '0' && element <= '9');
	}
}

bool is_identifier(int cont,std::string id){
	if(cont == static_cast<int>(id.size())-1){ 
		return ((id[cont] == ':'&&cont > 0)||process_elem_id(cont,id[cont]));
	} 
	
	return process_elem_id(cont,id[cont]) && is_identifier(++cont,id); 
}

bool is_reserved_key_word(std::string key){
	return validKeywords.count(key);
}

bool is_constant(int cont,std::string number){
	if(cont > static_cast<int>(number.size())-1)
		return false;

	if(static_cast<int>(number.size())-1 == cont)
		return true;
	
	return (((number[0] == '-'||number[0] == '+')&&!cont)||(number[cont] >= '0' && number[cont] <= '9')) && is_constant(++cont,number);
}

std::vector<Token> scan_line(std::string line){

	std::vector<Token> tokens;
	std::stringstream ss(line);
	std::string text;
	while(ss >> text){
		Token token;
		token.text = text;
		if(is_reserved_key_word(token.text)){
			token.type = Token::ReservedKeyWord;
		} else if(token.text == ","){
			token.type = Token::Delimiter;
		} else if(is_constant(0,token.text)||(token.text[0]=='0'&&token.text[1]=='x'&&is_constant(2,token.text))){
			token.type = Token::Constant;
		} else if(is_identifier(0,token.text)){
			token.type = Token::Identifier;
		} else{
		  throw AssemblerError("Caracter inválido", "Léxico");
		}
		tokens.push_back(token);
	}
	return tokens;
}
