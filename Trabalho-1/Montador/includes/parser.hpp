#pragma once
#include "scanner.hpp"
#include "sintaxerror.hpp"

bool not_is_identifier_operand(Token);
void parse_line(std::string);

