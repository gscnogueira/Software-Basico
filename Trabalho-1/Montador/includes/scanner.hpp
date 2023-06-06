#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <unordered_map>
#include <errors.hpp>

struct Token {
    enum TokenType {
        Identifier,ReservedKeyWord,Constant,Delimiter
	};
    TokenType type;
	std::string text;
};

std::vector<Token> scan_line(std::string line);
bool process_elem_id(int cont,char element);
bool is_identifier(int cont,std::string id);
bool is_reserved_key_word(std::string key);
bool is_constant(int cont,std::string number);
