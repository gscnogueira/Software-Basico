#include <code_generator.hpp>
#include <iostream>

void SymbolTable::insert(std::string symbol, unsigned int value ){

    if (defined.count(symbol))
        throw AssemblerError("Redefinição do símbolo \""+ symbol + "\"", "Semântico");

    values[symbol] = value;
    defined.insert(symbol);
}

void Program::gen_code(Line line)
{
    if(line.has_label_declaration()){
        std::cout<<"tem um label aqui!"<<std::endl;
        symb_table.insert(line.label, code.size());
    }

    if (line.is_instruction()){
        process_instruction(line);

    }
    else if (line.is_directive()){
        process_directive(line);
    }

    for (auto e : code)
        std::cout<<e<<" ";
    std::cout<<std::endl;
    std::cout<<code.size()<<std::endl;
    std::cout<<"-----"<<std::endl;
}

void Program::process_instruction(Line line){

    std::string instruction = line.cmd.text;
    int opcode = INSTRUCTION_TABLE.find(instruction)->second;

    code.push_back(opcode);

    for (auto token : line.args)
        if (token.type == token.Identifier)
            code.push_back(process_identifier(token));

}


int Program::process_identifier(Token token){

    int value;
    // se o identificador não está contido na tabela
    if (not symb_table.defined.count(token.text)){
        // insere valor na lista de pendências
        std::cout<<"Label desconhecido!"<<std::endl;
        symb_table.to_do_list[token.text] = -1;
        symb_table.values[token.text] = code.size();
        value = -1;
    }
    else {
        value = symb_table.values[token.text];
    }

    return value;

}


void Program::process_directive(Line line){

    std::string directive =  line.cmd.text;

    if (directive == "SPACE")
        process_space(line);

    if (directive =="CONST")
        process_const(line);

    if (directive == "EXTERN")
        process_extern(line);

    if (directive == "SECTION")
        process_section(line);
}

void Program::process_space(Line line){
    int n_spaces = line.args.size() ? stoi(line.args[0].text) : 1;
    for (int i = 0; i < n_spaces; i++)
        code.push_back(0);
}

void Program::process_const(Line line){}
void Program::process_extern(Line line){}
void Program::process_section(Line line){}
