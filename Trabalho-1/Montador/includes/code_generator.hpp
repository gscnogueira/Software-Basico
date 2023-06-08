# pragma once
#include <map>
#include <string>
#include <parser.hpp>
#include <errors.hpp>


typedef std::vector<std::pair<std::string, unsigned int>> def_table_t ;
typedef std::map<std::string, unsigned int> use_table_t ;


struct SymbolTable {

    std::map<std::string,unsigned int> values = {};
    std::set<std::string> defined = {};
    std::map<std::string,int> to_do_list = {};

    void insert(std::string symbol, unsigned int value);

};

struct Program {
    std::string name;
    SymbolTable symb_table;
    def_table_t def_table = {};
    use_table_t use_table = {};
    std::vector<int> code;

    Program(std::string name):name(name){}

    void gen_code(Line line);

private:
    void process_instruction(Line line);
    void process_directive(Line line);
    int process_identifier(Token token);
    void process_space(Line line);
    void process_const(Line line);
    void process_extern(Line line);
    void process_section(Line line);
};
