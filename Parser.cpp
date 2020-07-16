#include "Parser.hpp"
#include "string-util.hpp" 

Parser::Parser(ifstream &arq_gramatica, ifstream &arq_tabela_lr1) :
  gram(arq_gramatica),
  tabela(arq_tabela_lr1)
{
}

Arvore_parse Parser::executa_parse(istream &input) {
  vector<Token> tokens = Token::vetor_de_tokens(input);
  int pos = 0;
  int estado_atual = 0;
  do {
    //        cerr << "Estado:" << estado_atual << "pos=" << pos << "nome=" << tokens[pos].nome << ":" << tabela.simbolo_coluna[to_upper(tokens[pos].nome)] << endl;
        Transicao t;
        if (pos == tokens.size()){
          t = tabela.Tab[estado_atual][tabela.simbolo_coluna[string("$")]];
        } else {
          t = tabela.Tab[estado_atual][tabela.simbolo_coluna[tokens[pos].nome]];
        }
        //        cerr << t.impressao();
        //    cerr << "tipo=" << t.tipo<<endl;
    switch(t.tipo) {
    case 0: cerr << "CASO 0" <<endl;
      return Arvore_parse(NULL); break; //erro 
    case 1: // terminal
      {
        No_arv_parse * ap_no = new No_arv_parse;
        ap_no->tok = tokens[pos++];
        ap_no->regra = -1;
        pilha.push(make_pair(ap_no,estado_atual));
        estado_atual = t.prox_estado;
      }
      break;
    case 2: //goto
      cerr << "ERRO goto em lookahead."<<endl;
      return Arvore_parse(NULL);
    case 3: //reducao 
      {
        Regra r = gram.R[t.reducao];
        No_arv_parse * ap_no = new No_arv_parse;
        ap_no->tok = Token(r.esq, r.esq);
        ap_no->regra = t.reducao;
        ap_no->filhos.resize(r.dir.size());
        int estado = estado_atual;
        for(int i = 0; i < r.dir.size(); ++i) {
          ap_no->filhos[r.dir.size() - i - 1] = pilha.top().first;
          estado = pilha.top().second;
          pilha.pop();
        }
        pilha.push(make_pair(ap_no,estado));
        Transicao go_to = tabela.Tab[estado][tabela.simbolo_coluna[r.esq]];
        if (go_to.tipo != 2) {
          cerr << "ausencia de goto apos reducao" << endl;
          return Arvore_parse(NULL);
        }
        estado_atual = go_to.prox_estado;
        //cerr << ap_no->tok.nome << ":" << ap_no->regra << "," <<estado_atual << endl; fflush(stderr);
      }
      break;
    case 4: // accept
      return Arvore_parse(pilha.top().first);
    default:
      cerr << "Codigo invalido" << endl;
      return Arvore_parse(NULL);
    }
  }while(pos <= tokens.size());
  cerr << "CASO DEF" <<endl;
  return Arvore_parse(NULL);
}

