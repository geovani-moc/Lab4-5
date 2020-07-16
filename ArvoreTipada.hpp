#ifndef _ARVORE_TIPADA_HPP_
#define _ARVORE_TIPADA_HPP_
#include<vector>
#include<string>
using namespace std;
#include "Token.hpp"

class Token;
class Terminal {
public:
  Token tok;
  Terminal(Token t);
};

class ListaParametro;
class ListaDeclaracao;
class ListaComandos;
class Exp;
class Funcao;
class ID;
class Declaracao;
class Comando;
class Bloco;
class ListaExpressoes;



class Funcao {
public:
  ID *ident_funcao;
  ListaParametro *params;
  ListaDeclaracao *decls;
  ListaComandos *coms;
  Exp *exp_retorno;
  Funcao(ID *n, ListaParametro *p, ListaDeclaracao *d, ListaComandos *c, Exp *e);
};

//Implementar as seguintes classes

class ID{
public:
  string nome;
  ID(string n);
};
class Declaracao{
public:
  ID* identif;
  Declaracao(ID* id);
};
class ListaParametro{
public:
  Declaracao* dec;
  ListaParametro* prox;
  ListaParametro(Declaracao* d, ListaParametro* p);
};
class ListaComandos{
public:
  Comando* com;
  ListaComandos* prox;
  ListaComandos(Comando* c, ListaComandos* p);
};
class ListaDeclaracao{
public:
  Declaracao* dec;
  ListaDeclaracao* prox;
  ListaDeclaracao(Declaracao* d, ListaDeclaracao* l);

};

class Comando {
};

class ComandoBloco : public Comando {
public:
  Bloco* bloco;
  ComandoBloco(Bloco* b);
};

class ComandoAtrib : public Comando {
public:
  ID* id;
  Exp* exp;
  ComandoAtrib(ID* i, Exp* e);
};

class ComandoIF : public Comando {
public:
  Exp* cond;
  Comando* com;
  ComandoIF(Exp* condi, Comando* coma);
};

class ComandoWhile : public Comando {
public:
  Exp* cond;
  Comando* com;
  ComandoWhile(Exp* condi, Comando* coma);
};

class Bloco {
public:
  ListaDeclaracao* lista_dec;
  ListaComandos* lista_com;
  Bloco(ListaDeclaracao* lista_dec, ListaComandos* lista_com);
  
};

class Exp{
};

class ExpOper : public Exp {
public:
  Token operador;
  Exp* esq;
  Exp* dir;
  ExpOper(  Token operador, Exp* esq,Exp* dir);
};

class ExpID : public Exp {
public:
  ID* id;
  ExpID(ID* id);
};

class ExpNum : public Exp {
public:
  Token num;
  ExpNum(Token n);
};

class ExpChamada : public Exp {
public:
  ID* nome_funcao_chamada;
  ListaExpressoes* lista_exp;
  ExpChamada(ID* nom, ListaExpressoes* l);
};

class ListaExpressoes {
public:
  Exp* exp;
  ListaExpressoes* prox;
  ListaExpressoes(Exp* e, ListaExpressoes* l);
};
#endif
