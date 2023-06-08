# pragma once
#include <map>
#include <string>
#include <fstream>
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

	bool has_begin = false;
	bool has_end = false;
	bool has_directive = false;
    int text_end = -1;
    int text_begin = -1;
    int data_end = -1;
    int data_begin = -1;

    Program(std::string name):name(name){}

    void gen_code(Line line);
    void check_pendencies();
	 void check_directives();
    void write();

private:
    void resolve_label(std::string label);
    void process_instruction(Line line);
    void process_data_directive(Line line);
    void process_identifier(Token token);
    void process_space(Line line);
    void process_const(Line line);
    void process_extern(Line line);
    void process_section(Line line);
};

