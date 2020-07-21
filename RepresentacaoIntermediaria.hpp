#ifndef REPRESENTACAO_INTERMEDIARIA_HPP
#define REPRESENTACAO_INTERMEDIARIA_HPP

#include <string>

#include "Arvore.hpp"
#include "Frame.hpp"

#define SEQ (1)

using namespace std;

class No_arvore_RI
{
private:
    pair<int, string> representacao;
    vector<No_arvore_RI *> derivacao;

public:
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

public:
    Arvore_RI(Arvore_parse &arvore_parse);
};

#endif