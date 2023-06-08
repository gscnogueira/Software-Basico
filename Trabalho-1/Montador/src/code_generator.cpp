#include <code_generator.hpp>
#include <iostream>

void SymbolTable::insert(std::string symbol, unsigned int value ){

    if (values.find(symbol) != values.end())
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

        for (auto e : code)
            std::cout<<e<<" ";
        std::cout<<std::endl;
        std::cout<<code.size()<<std::endl;
    }
    else if (line.is_directive()){
        std::cout<<"Apenas uma diretivazinha ;-;\n";
    }

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


