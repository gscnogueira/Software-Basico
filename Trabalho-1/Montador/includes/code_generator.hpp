# pragma once
#include <map>
#include <string>
#include <fstream>
#include <parser.hpp>
#include <errors.hpp>


typedef std::map<std::string, std::vector<unsigned int>> use_table_t ;
typedef std::map<std::string, unsigned int> def_table_t ;


struct SymbolTable {

    std::map<std::string,unsigned int> values = {};
    std::set<std::string> defined = {};
    std::map<std::string,int> to_do_list = {};
    std::map<std::string,std::vector<std::string>> to_do_list_info = {};


    void insert(std::string symbol, unsigned int value);

};
struct Program {
    std::string name;
    SymbolTable symb_table;
    def_table_t def_table = {};
    use_table_t use_table = {};
    std::vector<int> code;
	std::map<unsigned int,int> offset_table;
    std::vector<int> relatives;

	bool has_begin = false;
	bool has_end = false;
    int text_end = -1;
    int text_begin = -1;
    int data_end = -1;
    int data_begin = -1;

    Program(std::string name):name(name){}

    void gen_code(Line line);
    void check_status();
    void write();

private:
    void resolve_label(std::string label);
    void process_instruction(Line line);
    void process_data_directive(Line line);
    void process_identifier(Token identifier, Token cmd);
    void process_space(Line line);
    void process_const(Line line);
    void process_extern(Line line);
    void process_public(Line line);
    void process_section(Line line);
    void process_linking_directive(Line line);
    void check_section_text();
    void check_pendencies();
    bool check_uses_data(std::string instruction);
    void update_def_table();
    void write_exc();
    void write_obj();
};

