#include "RepresentacaoIntermediaria.hpp"

No_arvore_RI::No_arvore_RI()
{
}

Arvore_RI::Arvore_RI(Arvore_parse &arvore_parse)
{
    frame = Frame(arvore_parse);
    raiz = NULL;
    contador_names = 0;
    
    gerar_representacao(arvore_parse);// tem que começar com um seq
}

void Arvore_RI::gerar_representacao(Arvore_parse &arvore_parse)
{
    raiz = new No_arvore_RI;

    raiz->representacao.first = SEQ;
    raiz->representacao.second = "";//colocar "seq"

    //adicionar um SEQ para W e return E

    raiz->derivacao.push_back(gerar_representacao(arvore_parse.raiz->filhos[7]));// tem que começar com um seq
    raiz->derivacao.push_back(gerar_representacao(arvore_parse.raiz->filhos[9]));
}

No_arvore_RI* Arvore_RI::gerar_representacao(No_arv_parse *no_arvore_parse)
{
    No_arvore_RI * nodo;
    int tamanho = (int)no_arvore_parse->filhos.size();
    string nome = no_arvore_parse->tok.nome;

    for (size_t i = 0; i < tamanho; ++i)
    {
        if(no_arvore_parse->filhos[i]->regra != -1) nodo = gerar_representacao(no_arvore_parse);
    }
    
    return nodo;
}