#include <stdio.h>
#include <algorithm>
#include<vector>
#include<string>
#include<iostream>
#include <fstream>
#include<sstream>
#include<map>
#include<stack>
using namespace std;

#include "Gramatica.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"
#include "IRParse.hpp"

int main(int argc, char * argv[]) {
  if (argc != 3 && argc != 1) {
    cerr << "Parametros nomes dos arquivos: 1) gramática e 2) lista de mapeamentos da tabela LR1" << endl;
    return 1;
  }
  string nome_gramatica, nome_tab_lr1;
  if (argc == 1) {
    //cerr << "Valores padrao utilizados: gramatica.conf e tabela_lr1.conf" << endl;                              
    nome_gramatica = string("gramatica.txt");
    nome_tab_lr1 = string("tabela.txt");
  } else {
    nome_gramatica = string(argv[1]);
    nome_tab_lr1 = string(argv[2]);
  }


  ifstream arq_gramatica(nome_gramatica);
  ifstream arq_tabela_lr1(nome_tab_lr1);
  if (arq_tabela_lr1.fail() || arq_gramatica.fail()) {
    cerr << "Falha ao abrir arquivos: " <<
      ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " <<
      ((arq_tabela_lr1.fail()) ? nome_tab_lr1 : "") << endl;
    return 1;
  }
  Parser parser(arq_gramatica, arq_tabela_lr1);
  //  parser.tabela.debug();
  Arvore_parse arv = parser.executa_parse(cin);
  Funcao * func = arv.extrai_funcao();

  IRParse ir_parser;
  cerr << func->ident_funcao->nome <<endl;
  cerr << func->params->dec->identif->nome <<endl;
  cerr << func->coms->prox->com->TypeClass() << endl;
  
  Stm_ir* IR = ir_parser.extrai_funcao(func);
  return 0;
}
