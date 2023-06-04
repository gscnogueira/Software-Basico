#pragma once
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <errors.hpp>
#include <fstream>
#include <utility>


typedef unsigned int uint;
typedef std::vector<std::pair<std::string, uint>> use_table;
typedef std::map<std::string, uint> def_table;

struct Module
{
  std::string nome;
  use_table tabela_de_uso;
  def_table tabela_de_definicoes;
  std::vector<uint>relativos;
  std::vector<uint>code;

  Module(std::string file_name);

  Module(std::string nome, use_table uso, def_table def,
	 std::vector<uint> rel, std::vector<uint> code)
    :nome(nome), tabela_de_uso(uso),
     tabela_de_definicoes(def), relativos(rel),
     code(code){}
  void write_exec();
};

Module link(Module mod_a, Module mod_b);

def_table gen_global_definition_table(Module a,
				      Module b);

std::vector<uint> apply_use_table(Module m,
				  def_table g_dt,
				  const uint fator_de_correcao);

std::vector<uint> join_relativos(Module a, Module b);
