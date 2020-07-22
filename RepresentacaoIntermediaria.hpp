#ifndef REPRESENTACAO_INTERMEDIARIA_HPP
#define REPRESENTACAO_INTERMEDIARIA_HPP

#include <string>

#include "Arvore.hpp"
#include "Frame.hpp"

#define NENHUM (0)
#define SEQ (1)
#define IF (2)
#define WHILE (3)
#define ATRIBUICAO (4)
#define VARIAVEL (5)
#define CONSTANTE (6)
#define BINOP (7)
#define FUNCAO (8)

using namespace std;

class No_arvore_RI
{
public:
    pair<string, string> representacao;
    vector<No_arvore_RI *> derivacao;

    No_arvore_RI();
};

class Arvore_RI
{
private:
    No_arvore_RI *raiz;
    Frame frame;
    int contador_names;

    void gerar_representacao(Arvore_parse &arvore_parser);
    No_arvore_RI *gerar_representacao(No_arv_parse *no_arvore_parse);
    int definir_caso(int regra);

    No_arvore_RI *binop(string &operacao, No_arvore_RI *no1, No_arvore_RI *no2);
    No_arvore_RI *variavel(No_arv_parse *no);
    
public:
    Arvore_RI(Arvore_parse &arvore_parse);
};

#endif