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
        symb_table.insert(line.label, code.size());
        resolve_label(line.label);
    }

    if (line.is_instruction()){
        process_instruction(line);

    }
    else if (line.is_directive()){
        process_directive(line);
    }
}

void Program::resolve_label(std::string label) {
     // verifica se simbolo possui lista de pendências;
     if (symb_table.to_do_list.find(label) == symb_table.to_do_list.end())
         return ;

     int prox = symb_table.to_do_list[label];
     int aux;

     while(prox!=-1){
         aux = code[prox];
         code[prox] = symb_table.values[label];
         prox = aux;
     }
}

void Program::process_instruction(Line line){

    std::string instruction = line.cmd.text;
    int opcode = INSTRUCTION_TABLE.find(instruction)->second;

    code.push_back(opcode);

    for (auto token : line.args)
        if (token.type == token.Identifier)
            process_identifier(token);

}


void Program::process_identifier(Token token){

    int value;
    std::string label = token.text;

    // se o identificador não está contido na tabela
    if (not symb_table.defined.count(label)){

        // verifica se já existem pendencias para esse identificador
        if (symb_table.to_do_list.find(label) == symb_table.to_do_list.end())
            symb_table.to_do_list[label] = -1;

        // atualiza lista de pendencias
        value = symb_table.to_do_list[label];
        symb_table.to_do_list[label] = code.size();
    }
    else {
        value = symb_table.values[token.text];
    }

    code.push_back(value);
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

void Program::process_const(Line line){
    int const_n = stoi(line.args[0].text);
    code.push_back(const_n);
}

void Program::process_extern(Line line){}

void Program::process_section(Line line){}

void Program::write(){
    std::string file_name = name + ".exc";
    std::ofstream output_file(file_name);
    for (auto e: code)
        output_file << e << " ";
}
