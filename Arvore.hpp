#ifndef _ARVORE_HPP_
#define _ARVORE_HPP_
#include<vector>
#include<string>
using namespace std;
#include "Token.hpp"
#include "ArvoreTipada.hpp"

class Token;
class No_arv_parse {
public:
  Token tok;
  int regra; // -1 = terminal
  vector<No_arv_parse *> filhos;
  No_arv_parse();
};

class Arvore_parse {
private:
  Funcao * extrai_funcao(No_arv_parse * no);
  ID * extrai_ID(No_arv_parse * no);
  ListaParametro* extrai_ListaParametro(No_arv_parse * no);
  ListaDeclaracao* extrai_ListaDeclaracao(No_arv_parse * no);
  ListaComandos* extrai_ListaComandos(No_arv_parse * no);
  Exp* extrai_Exp(No_arv_parse * no);
  Declaracao* extrai_Declaracao(No_arv_parse * no);
  Comando* extrai_Comando(No_arv_parse * no);
  Bloco* extrai_Bloco(No_arv_parse * no);
  ListaExpressoes* extrai_ListaExpressoes(No_arv_parse * no);
  
  
public:
  No_arv_parse * raiz;
  Arvore_parse(No_arv_parse * rr);
  void imprime(No_arv_parse * no);
  void debug();
  Funcao* extrai_funcao();
};

#endif
