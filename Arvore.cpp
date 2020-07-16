#include "Arvore.hpp"
#include<iostream>
#include<string>
using namespace std;

No_arv_parse::No_arv_parse(): tok(Token(string(""),string(""))) {
  regra = -1; //terminal
  filhos.clear();
}

Arvore_parse::Arvore_parse(No_arv_parse * rr) {
  raiz = rr;
}

void Arvore_parse::imprime(No_arv_parse * no) {
  cerr << "[" <<no->tok.nome<< "," << no->tok.imagem <<","<< no->regra  << ":";
  for (int i = 0; i < no->filhos.size(); ++i) {
    imprime(no->filhos[i]);
  }
  cerr << "]";
}

void Arvore_parse::debug(){
  imprime(raiz);
  cerr << endl;
}

ID * Arvore_parse::extrai_ID(No_arv_parse * no) {
  return new ID(no->tok.imagem);
}

Funcao * Arvore_parse::extrai_funcao(No_arv_parse * no) {
  cerr << endl<<" @@ "<< endl;
  if (no==NULL) cerr << " NULL " << endl;
  if (no->regra != 1) {
    cerr << "Erro conversao"<< endl;
    return NULL;
  }
  cerr << endl<<"###"<< endl;
  return new Funcao(extrai_ID(no->filhos[1]), 
                    extrai_ListaParametro(no->filhos[3]),
                    extrai_ListaDeclaracao(no->filhos[6]),
                    extrai_ListaComandos(no->filhos[7]),
                    extrai_Exp(no->filhos[9]));
}
Funcao * Arvore_parse::extrai_funcao() {
  return extrai_funcao(raiz);
}

ListaParametro* Arvore_parse::extrai_ListaParametro(No_arv_parse * no){
  if (no->regra == 2){
    return new ListaParametro(extrai_Declaracao(no->filhos[0]),NULL);    
  }
  if (no->regra == 3) {
    return new ListaParametro(extrai_Declaracao(no->filhos[0]),
                              extrai_ListaParametro(no->filhos[2]));
  }
}

ListaDeclaracao* Arvore_parse::extrai_ListaDeclaracao(No_arv_parse * no){
  if (no->regra == 6) return NULL;
  return new ListaDeclaracao(extrai_Declaracao(no->filhos[0]), 
                             extrai_ListaDeclaracao(no->filhos[2]));
}

ListaComandos* Arvore_parse::extrai_ListaComandos(No_arv_parse * no){
  if (no->regra == 9) return NULL;
  return new ListaComandos(extrai_Comando(no->filhos[0]), extrai_ListaComandos(no->filhos[1]));
}

Exp* Arvore_parse::extrai_Exp(No_arv_parse * no){
  if (no->regra >=14 && no->regra <=23) {
    return new ExpOper(no->filhos[1]->tok, extrai_Exp(no->filhos[0]), extrai_Exp(no->filhos[2]));
  }
  if (no->regra == 24) {
    return extrai_Exp(no->filhos[1]);
  }
  if (no->regra == 25) {
    return new ExpID(extrai_ID(no->filhos[0]));
  }
  if (no->regra == 26) {
    return new ExpNum(no->filhos[0]->tok);
  }
  if (no->regra == 27) {
    return new ExpChamada(extrai_ID(no->filhos[0]), extrai_ListaExpressoes(no->filhos[2]));
  }
}

Declaracao* Arvore_parse::extrai_Declaracao(No_arv_parse * no){
  return new Declaracao(extrai_ID(no->filhos[1]));
}
 
Comando* Arvore_parse::extrai_Comando(No_arv_parse * no){
   if (no->regra == 10) return new ComandoBloco(extrai_Bloco(no->filhos[0]));
   if (no->regra == 11) return new ComandoAtrib(extrai_ID(no->filhos[0]), extrai_Exp(no->filhos[2]));
   if (no->regra == 12) return new ComandoIF(extrai_Exp(no->filhos[2]), extrai_Comando(no->filhos[4]));
   if (no->regra == 13) return new ComandoWhile(extrai_Exp(no->filhos[2]), extrai_Comando(no->filhos[4]));

 }

Bloco* Arvore_parse::extrai_Bloco(No_arv_parse * no){
  return new Bloco(extrai_ListaDeclaracao(no->filhos[1]), extrai_ListaComandos(no->filhos[2]));
}

ListaExpressoes* Arvore_parse::extrai_ListaExpressoes(No_arv_parse * no){
  if (no->regra ==28) return new ListaExpressoes(extrai_Exp(no->filhos[0]), NULL);
  if (no->regra ==29) return new ListaExpressoes(extrai_Exp(no->filhos[0]), extrai_ListaExpressoes(no->filhos[2]));
}

