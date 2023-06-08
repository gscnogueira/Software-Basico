#pragma once
#include <scanner.hpp>
#include <instruction_table.hpp>
#include <vector>

struct Line {
  std::string label;
  Token cmd;
  std::vector<Token> args;
  Line(std::string label,
       Token cmd,
       std::vector<Token> args): label(label), cmd(cmd), args(args) {}
  bool is_instruction() const;
  bool has_label_declaration() const;
};

bool not_is_identifier_operand(Token);
Line parse_line(std::string);

