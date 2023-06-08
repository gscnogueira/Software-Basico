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
    if (line.is_section())
        process_section(line);

    if (line.is_instruction()){
        if (text_begin==-1)
            throw AssemblerError("Instrução executada fora da seção TEXT", "Semântico");
        process_instruction(line);

    }
    else if (line.is_data_directive()){
        if (data_begin==-1 || (data_end != -1 && (int) code.size() > data_end ))
            throw AssemblerError("Dado definido fora da seção DATA", "Semântico");
        process_data_directive(line);
    }
}

void Program::resolve_label(std::string label) {
    // verifica se simbolo possui lista de pendências
    auto it = symb_table.to_do_list.find(label);

    if ( it == symb_table.to_do_list.end() )
        return ;

    // remove lista de pendencias do simbolo
    int prox = (*it).second;
    symb_table.to_do_list.erase(it);
    int aux;

    // substiui ocorrências 
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

void Program::process_data_directive(Line line){

    std::string directive =  line.cmd.text;

    if (directive == "SPACE")
        process_space(line);

    if (directive =="CONST")
        process_const(line);

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

void Program::process_section(Line line){
    std::string arg = line.args[0].text;
    if (arg == "TEXT"){
        text_begin=code.size();
        data_end = data_begin == -1 ? -1 : code.size();
    }
    else if (arg == "DATA"){
        data_begin=code.size();
        text_end = text_begin == -1 ? -1 : code.size();
    }
}

void Program::write(){
    std::string file_name = name + ".exc";
    std::ofstream output_file(file_name);
    for (auto e: code)
        output_file << e << " ";
}

void Program::check_pendencies(){
    for (auto e : symb_table.to_do_list){
		std::string msg = e.first + " não foi definido" ;
        throw AssemblerError(msg, "Semântico");
    }

}
