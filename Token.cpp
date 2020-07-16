#include "Token.hpp" 
#include "string-util.hpp" 
#include<vector>
#include<string>
#include <sstream>
#include <iostream>
#define TAM_LIN 1000

using namespace std;

Token::Token(string n, string im): nome(n), imagem(im) {}

vector<Token> Token::vetor_de_tokens(istream &arq) {
  vector<Token> result;
  while(!arq.eof()) {
    char lin_aux[TAM_LIN];
    arq.getline(lin_aux, TAM_LIN-1, '\n');
    string linha(lin_aux);
    istringstream input_lin(linha);

    char nome_aux[TAM_LIN];
    input_lin.getline(nome_aux, TAM_LIN-1, ' ');
    string nome_token(nome_aux);

    if (nome_token.size() > 0) {
      char im_aux[TAM_LIN];
      im_aux[0]='\0';
      input_lin.getline(im_aux, TAM_LIN-1, '\n');
      string imagem_token_possivel(im_aux);

      //cerr << "nome_token=[" << nome_token << "]" << "imagem_token=[" << imagem_token_possivel << "]" << endl;

      string imagem_token = ((imagem_token_possivel.size() > 0) ? imagem_token_possivel : nome_token);

      Token tok(to_upper(nome_token), imagem_token);

      //cerr << "Token=[" << tok.nome << "]-[" << tok.imagem << "]" << endl << endl;

      result.push_back(tok);
    }
  }
  return result;
}


