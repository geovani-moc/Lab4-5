#include "ArvoreTipada.hpp" 

Funcao::Funcao(ID *n, ListaParametro *p, ListaDeclaracao *d, ListaComandos *c, Exp *e):
  ident_funcao(n), params(p), decls(d), coms(c), exp_retorno(e) {}

ListaParametro::ListaParametro(Declaracao* d, ListaParametro* p): dec(d), prox(p) {}
ListaComandos::ListaComandos(Comando* c, ListaComandos* p): com(c), prox(p) {}
ListaDeclaracao::ListaDeclaracao(Declaracao* d, ListaDeclaracao* l): dec(d), prox(l) {}
Declaracao::Declaracao(ID* id): identif(id) {} 
ID::ID(string n): nome(n) {}

ComandoBloco::ComandoBloco(Bloco* b): bloco(b) {}
ComandoAtrib::ComandoAtrib(ID* i, Exp* e): id(i), exp(e) {}
ComandoIF::ComandoIF(Exp* condi, Comando* coma): cond(condi), com(coma){}
ComandoWhile::ComandoWhile(Exp* condi, Comando* coma): cond(condi), com(coma){}

Bloco::Bloco(ListaDeclaracao* l_dec, ListaComandos* l_com): lista_dec(l_dec), lista_com(l_com){}
ExpOper::ExpOper(  Token op, Exp* e,Exp* d): operador(op), esq(e), dir(d) {}
ExpID::ExpID(ID* ide): id(ide) {}
ExpNum::ExpNum(Token n):num(n){}
ExpChamada::ExpChamada(ID* nom, ListaExpressoes* l): nome_funcao_chamada(nom), lista_exp(l) {}
ListaExpressoes::ListaExpressoes(Exp* e, ListaExpressoes* l): exp(e), prox(l) {}

string ComandoBloco::TypeClass() { return "ComandoBloco"; }
string ComandoAtrib::TypeClass() { return "ComandoAtrib"; }
string ComandoIF::TypeClass() { return "ComandoIF"; }
string ComandoWhile::TypeClass() { return "ComandoWhile"; }

string ExpOper::TypeClass() { return "ExpOper"; }
string ExpID::TypeClass() { return "ExpID"; }
string ExpNum::TypeClass() { return "ExpNum"; }
string ExpChamada::TypeClass() { return "ExpChamada"; }