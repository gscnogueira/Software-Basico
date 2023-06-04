#include <linker.hpp>

Module::Module (std::string file_name)
{
  std::ifstream input(file_name+".obj");
  std::string line, section;
  std::vector<std::string> sections {"CODE", "RELATIVOS", "DEF", "USO"};

  if(input.fail())
    throw LinkerError("Arquivo " + file_name + ".obj não existe");

  nome = file_name;
  
  while(std::getline(input, line)){

    // caso o arquivo fonte tenha sido escrito no windows
    if (!line.empty() && line.back() == '\r') 
      line.erase(line.size() - 1);

    std::stringstream ss(line);

    if (line==sections.back()){
      section=sections.back();
      sections.pop_back();
      continue;
    }
    else if (section ==  "USO"){
      std::string label;
      uint address;
      ss>>label>>address;
      tabela_de_uso.push_back({label, address});
    }
    else if (section == "DEF"){
      std::string label;
      uint address;
      ss >> label >> address;
      tabela_de_definicoes[label]=address;
    }
    else if (section == "RELATIVOS"){
      uint tmp;
      while(ss>>tmp)
	relativos.push_back(tmp);
    }
    else if (section == "CODE"){
      uint tmp;
      while(ss>>tmp)
	code.push_back(tmp);
    }
  }
}

void Module::write_exec(){
  std::ofstream output (nome+".exc");
  for (auto e : code)
    output << e << " ";
}

Module link(Module mod_a, Module mod_b)
{

  const uint fator_correcao_a = 0;
  const uint fator_correcao_b = mod_a.code.size();

  // Gera tabela global de definicoes
  def_table global_def_table = gen_global_definition_table(mod_a, mod_b);

  // Aplica tabela de uso em mod_a e corrige relativos
  auto code_a = apply_use_table(mod_a, global_def_table,
				fator_correcao_a);

  // Aplica tabela de uso em mod_a b corrige relativos
  auto code_b = apply_use_table(mod_b, global_def_table,
				fator_correcao_b);

  code_a.insert(code_a.end(), code_b.begin(), code_b.end());

  // junta relativos
  auto relativos = join_relativos(mod_a, mod_b);

  return Module(mod_a.nome,
		{},
		global_def_table,
		relativos,
		code_a) ;
}

def_table gen_global_definition_table(Module a, Module b)
{
 uint fator_de_correcao = a.code.size();
 def_table g_dt = a.tabela_de_definicoes;

 for (auto e : b.tabela_de_definicoes)
   g_dt[e.first] = e.second + fator_de_correcao;

 return g_dt;
}

std::vector<uint> apply_use_table(Module m, def_table g_dt,
				  const uint fator_de_correcao)
{
  std::string label;
  uint addr;
  std::vector<uint> code = m.code;
  std::vector<bool> corrected(m.relativos.size(), false);
  for (auto e : m.tabela_de_uso){
    label = e.first;
    addr = e.second;
    code[addr] += g_dt[label];
    corrected[addr]=true;
  }
  for (auto e: m.relativos){
    if (corrected[e]) continue;
    code[e]+=fator_de_correcao;
    corrected[e]=true;
  }

  return code;
}

std::vector<uint> join_relativos(Module a, Module b)
{
  uint fator_de_correcao = a.code.size();
  auto relativos_a = a.relativos;
  auto relativos_b = b.relativos;

  for (auto& e : relativos_b) e += fator_de_correcao;

  relativos_a.insert(relativos_a.end(), relativos_b.begin(),
		     relativos_b.end());
  return relativos_a;
}
