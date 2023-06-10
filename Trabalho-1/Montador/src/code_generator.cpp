#include <code_generator.hpp>
#include <iostream>
#include <algorithm>

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
        if(line.is_data_directive())
            data_identifiers.insert(line.label);
    }
    if (line.is_section())
        process_section(line);

    else if (line.is_instruction()){
        if (text_begin==-1)
            throw AssemblerError("Instrução executada fora da seção TEXT", "Semântico");
        process_instruction(line);

    }
    else if (line.is_data_directive()){
        if (data_begin==-1 || (data_end != -1 && (int) code.size() > data_end ))
            throw AssemblerError("Dado definido fora da seção DATA", "Semântico");
        process_data_directive(line);
    }
    else if(line.is_linking_directive())
        process_linking_directive(line);

}

void Program::process_linking_directive(Line line){
    if (line.cmd.text == "EXTERN:"){
        process_extern(line);
	}
    else if (line.cmd.text == "PUBLIC"){
        process_public(line);
	}
	else if(line.cmd.text == "BEGIN"){
		has_begin = true;
	}
	else if(line.cmd.text == "END"){
        if (not has_begin)
			throw AssemblerError("Diretiva END não possui BEGIN correspondente", "Semântico");
        else
            has_end = true;
	}
}

void Program::process_public(Line line){
	if(!has_begin)
		 throw AssemblerError("Diretiva PUBLIC pode ser utilizada apenas em módulos", "Semântico");
    auto arg = line.args[0].text;
    def_table[arg] = 0;

}

void Program::process_extern(Line line){
	if(!has_begin)
		 throw AssemblerError("Diretiva EXTERN pode ser utilizada apenas em módulos", "Semântico");
    auto arg = line.args[0].text;
    use_table.insert({arg, {}});
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
    auto label_info = symb_table.to_do_list_info.find(label);

    // substiui ocorrências 
    while(prox!=-1){
        aux = code[prox];
        code[prox] = symb_table.values[label]+offset_table[prox];
        prox = aux;
        label_info->second.pop_back();
    }

    symb_table.to_do_list_info.erase(label_info);
}

void Program::process_instruction(Line line){

    std::string instruction = line.cmd.text;
    int opcode = INSTRUCTION_TABLE.find(instruction)->second;

    code.push_back(opcode);
	int limit = line.args.size();
    for (int i =0; i < limit;++i){
        if (line.args[i].type == line.args[i].Identifier){
            int index = code.size();
			if(i+2 < limit&&line.args[i+1].text == "+"){
				offset_table[index] = stoi(line.args[i+2].text);
			}
			process_identifier(line.args[i], line.cmd);
		}
	}
}

void Program::process_identifier(Token id, Token cmd){

    int value;
    std::string label = id.text;

    // verifica se o identificador é externo
    if (use_table.find(label) != use_table.end()){
        use_table[label].push_back(code.size());
        value = offset_table[code.size()];
    }
    // se o identificador não está contido na tabela de definições
    else if (not symb_table.defined.count(label)){

        // verifica se já existem pendencias para esse identificador
        if (symb_table.to_do_list.find(label) == symb_table.to_do_list.end())
            symb_table.to_do_list[label] = -1;

        // atualiza lista de pendencias
        value = symb_table.to_do_list[label];
        symb_table.to_do_list[label] = code.size();
        symb_table.to_do_list_info[label].push_back(cmd.text);
    }
    // se o identificador está contido na tabela de símbolos
    else {
        value = symb_table.values[label];
    }

    if(data_identifiers.count(label))
        data_positions.push_back(code.size());

    relatives.push_back(code.size());
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
    if (has_begin and has_end){
        write_obj();
    }
    else {
        write_exc();
    }
}

void Program::write_exc(){
    std::string file_name;
    std::ofstream output_file(file_name);

    file_name = name + ".exc";
    output_file.open(file_name);

    for (auto e: code)
        output_file << e << " ";
}
void Program::write_obj(){
    std::string file_name;
    std::ofstream output_file(file_name);

    file_name = name + ".obj";
    output_file.open(file_name);

    update_def_table();

    output_file<<"USO" << std::endl;

    for (auto e : use_table){
        std::string symbol = e.first;
        for (auto addr : e.second)
            output_file << symbol << " " << addr <<std::endl;
    }

    output_file<<"DEF" << std::endl;

    for (auto e : def_table)
        output_file << e.first << " " << e.second <<std::endl;

    output_file<<"RELATIVOS" << std::endl;

    for (auto e : relatives)
        output_file << e << " ";
    output_file<<std::endl;

    output_file<<"CODE" << std::endl;

    for (auto e : code)
        output_file << e << " ";
    output_file<<std::endl;
}

void Program::update_def_table(){
    for (auto& e : def_table)
        e.second = symb_table.values[e.first];
}

void Program::check_pendencies(){
    for (auto e : symb_table.to_do_list_info){
        auto label = e.first;
        for (auto instruction : e.second){
            bool uses_data = check_uses_data(instruction);
            std:: string label_type = uses_data ? "Dado " : "Rótulo ";
            std:: string section_type = uses_data ? "DATA" : "TEXT";
            std::string msg = label_type + label + " não foi definido na seção "+ section_type ;
            throw AssemblerError(msg, "Semântico");
        }
    }
}

bool Program::check_uses_data(std::string instruction){
    std::set<std::string> label_instructions = { "JMP", "JMPP", "JMPN", "JMPZ"};
    return not label_instructions.count(instruction);
};

void Program::check_section_text(){
    if( text_begin == -1)
        throw AssemblerError("Seção TEXT faltante", "Semântico");
        
}

void Program::align_sections(){
    if (text_begin < data_begin  or data_begin == -1)
        return ;

    int data_size = data_end - data_begin;
    int offset = code.size() - data_size;
    std::cout<<data_size<<std::endl;
    std::cout<<offset<<std::endl;

    // atualiza tabela de símbolos
    for (auto &e: symb_table.values){
        if(data_identifiers.find(e.first)!=data_identifiers.end())
            e.second += offset;
        else
            e.second -= data_size;
    }

    // atualiza tabela de uso
    for (auto &m : use_table){
        for(auto &e : m.second)
            e-=data_size;
    }

    // atualiza código
    for (auto e: data_positions)
        code[e]+=offset;

    //atualiza relativos 
    for (auto& e: relatives)
        e-=data_size;


    std::rotate(code.begin(), code.begin()+data_size, code.end());

    return;
}
void Program::check_status(){
    check_pendencies();
    check_section_text();
    align_sections();
	if(has_begin ^ has_end){
		if(has_begin)
			throw AssemblerError("Diretiva BEGIN não possui END correspondente", "Semântico");
		else
			throw AssemblerError("Diretiva END não possui BEGIN correspondente", "Semântico");
	}
}
