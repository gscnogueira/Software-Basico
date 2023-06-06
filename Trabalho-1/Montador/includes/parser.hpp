#pragma once
#include "scanner.hpp"
#include <vector>

struct Line {
  std::vector<Token> tokens;
  Line(std::vector<Token> tokens): tokens(tokens) {}
};

bool not_is_identifier_operand(Token);
Line parse_line(std::string);

