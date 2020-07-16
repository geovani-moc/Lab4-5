#ifndef _TABELALR1_HPP_
#define _TABELALR1_HPP_
#include<vector>
#include<string>
#include<iostream>
#include<fstream>   
#include<sstream>
#include<map>
using namespace std;

class Transicao {
public:
  int tipo; // 0-vazio, 1 - shift, 2 - goto, 3-reduz, 4-aceita
  int reducao; // qual regra no vetor de gramatica
  int prox_estado;
  string impressao();
  Transicao();
  Transicao(string tok); 
};

class Tabela_LR1 {
  int num_simbolos;
  int mapeia_simbolo(string s);
public:
  map<string,int> simbolo_coluna;
  map<int, map<int, Transicao> > Tab;
  void debug();
  Tabela_LR1(ifstream &arq_tabela_lr1);
};

#endif
