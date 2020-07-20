#include "RepresentacaoIntermediaria.hpp"

Representacao_intermediaria::Representacao_intermediaria(Arvore_parse &arvore)
{
    frame = Frame(arvore);
    criar_representacao(arvore);
}

Representacao_intermediaria::~Representacao_intermediaria()
{
}

string Representacao_intermediaria::get_representaocao_intermediaria()
{
    return representacao_intermediaria;
}

void Representacao_intermediaria::criar_representacao(Arvore_parse &arvore)
{
    No_arv_parse *raiz = arvore.raiz;

    int tamanho = (int)raiz->filhos.size();

    // olhar se e necessario identificar paramentros
    // por exemplo: associar o paramentro "n" com parametro1

    for (int i = 6; i < tamanho; ++i)
    {
        if (raiz->filhos[i]->regra != -1)
            criar_representacao(raiz->filhos[i]);
    }
}

void Representacao_intermediaria::criar_representacao(No_arv_parse *nodo)
{
    int caso = identifica_caso(nodo);

    switch (caso)
    {
    case IF:
        break;
    case WHILE:
        break;
    case ATRIBUICAO:
        break;
    case CHAMADA_DE_FUNCAO:
        break;
    case ACESSO_DE_VARIAVEL:
        break;
    case ACESSO_DE_CONSTANTE:
        break;
    case OPERACAO_BINARIA:
        break;
    default:
        break;
    }
}

int Representacao_intermediaria::identifica_caso(No_arv_parse *nodo)
{
    return 1;
}