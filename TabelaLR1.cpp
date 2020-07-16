#include "TabelaLR1.hpp"
#include "string-util.hpp"

#include<vector>
#include<string>
#include<iostream>
#include<fstream>   
#include<sstream>
using namespace std;

Transicao::Transicao() {
  tipo = 0;
  reducao = prox_estado = -1;
}

Transicao::Transicao(string tok){
  tipo = reducao = prox_estado = -1;
  if (tok.size() == 0) {
    tipo = 0; //vazio
  } else if (tok[0] == 's') {
    tipo = 1; //shift
    //      cerr << "convertendo:" << tok.substr(1) << endl;
    prox_estado = stoi(tok.substr(1));
  } else if (tok[0] == 'a') {
    tipo = 4; //aceita
  }else if (tok[0] == 'g') {
    tipo = 2; // goto
    //      cerr << "convertendo:" << tok << endl;
    prox_estado = stoi(tok.substr(1));
  } else if (tok[0] == 'r') {// == r
    tipo = 3; //reducao
    //      cerr << "convertendo:" << tok.substr(1) << endl;
    reducao = stoi(tok.substr(1));
  } else {
    cerr << " Erro na geracao de transicao"  << endl;
  }
}

string Transicao::impressao() {
  string T = ((tipo == 0) ? "X" : (tipo == 1) ? "shift:" : (tipo == 2) ? "goto:" : (tipo==3) ? "reduz:" : (tipo == 4) ? "aceita" : "Y");
  string res = "(" + T + ",r=" + to_string(reducao) + ",prox=" + to_string(prox_estado) + ")";
  return res;
}

int Tabela_LR1::mapeia_simbolo(string s){
  map<string, int>::iterator it = simbolo_coluna.find(to_upper(s));
  if (it != simbolo_coluna.end()){
    return (it->second);
  }
  simbolo_coluna[s] = (num_simbolos++);
  return num_simbolos-1;
}
 
Tabela_LR1::Tabela_LR1(ifstream &arq_tabela_lr1) {
  num_simbolos = 0;
  vector<vector<string> > mat = matriz_de_arquivo(arq_tabela_lr1, '\n', ' ');
  if (mat[mat.size()-1].size() == 1) mat.pop_back(); //remove ultima linha vazia.
  //    debug_mat(mat);
  for (int lin = 0; lin < mat.size(); ++lin) {
    int estado = stoi(mat[lin][0]);
    string lookahead = to_upper(mat[lin][1]);
    int lookahead_numerado = mapeia_simbolo(lookahead);
    string acao = mat[lin][2];
    //    cerr << "[" <<estado << "]["<< lookahead_numerado <<"," <<lookahead << "]=" <<acao<< endl;
    if (Tab.find(estado)==Tab.end()) Tab[estado] = map<int,Transicao>();
    Tab[estado][lookahead_numerado] = Transicao(acao);
  }
}

void Tabela_LR1::debug() {
  cerr << "Simbolo_coluna" << endl;
  for (map<string,int>::iterator it = simbolo_coluna.begin();
       it != simbolo_coluna.end();
       ++it) {
    cerr << "(" << it->first << "," << it->second << "),";
  }
  cerr << endl;
  cerr << "Tabela(" << Tab.size() << ")" << endl;
  for (int i = 0; i < Tab.size(); ++i) {
    for (int j = 0; j < Tab[i].size(); ++j) {
      Transicao t = Tab[i][j];
      int tipo = t.tipo;
      cerr << ((tipo == 0) ? "" :(tipo == 1 ? "s" : (tipo == 3 ? "r" : (tipo == 4 ? "acc" : ""))));
      if (tipo == 1 || tipo == 2) {//shift e goto
        cerr << t.prox_estado;
      } else if (tipo == 3) {
        cerr << t.reducao;
      }
      cerr << ";";
    }
    cerr << endl;
  }
}

