#ifndef _TOKEN_
#define _TOKEN_
#include<vector>
#include<string>
#include <sstream>
#include <iostream>

using namespace std;

class Token {
public:
  string nome;
  string imagem;
  Token(string n, string im);
  static vector<Token> vetor_de_tokens(istream &arq);
};

#endif
