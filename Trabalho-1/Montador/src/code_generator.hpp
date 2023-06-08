# pragma once
#include <parser.hpp>
#include <map>
#include <string>

typedef map<std::string, pair<unsigned int, bool>> symb_table_t ;
typedef vector<pair<std::string, unsigned int>> def_table_t ;
typedef map<std::string, unsigned int> use_table_t ;

struct Program {
    std::string name;
    symb_table_t symb_table = {};
    def_table_t def_table = {};
    use_table_t use_table = {};

    Program(std::string name):name(name);

    void gen_code(Line line);
};

