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
    //representar sequencia, falta adicionar
    switch (caso)
    {
    case IF:
        representar_if();
        break;
    case WHILE:
        representar_while();
        break;
    case ATRIBUICAO:
        representar_atribuicao();
        break;
    case CHAMADA_DE_FUNCAO:
        representar_chamada_de_funcao();
        break;
    case ACESSO_DE_VARIAVEL:
        representar_acesso_de_variavel();
        break;
    case ACESSO_DE_CONSTANTE:
        representar_acesso_de_constante();
        break;
    case OPERACAO_BINARIA:
        representar_operacao_binaria();
        break;
    default:
        break;
    }
}

int Representacao_intermediaria::identifica_caso(No_arv_parse *nodo)
{
    return 1;
}

void Representacao_intermediaria::representar_if(No_arv_parse *condicao, No_arv_parse *bloco)
{}
void Representacao_intermediaria::representar_while(No_arv_parse *condicao, No_arv_parse *bloco)
{}
void Representacao_intermediaria::representar_atribuicao(No_arv_parse *nodo)
{}
void Representacao_intermediaria::representar_chamada_de_funcao(No_arv_parse *nodo)
{}
void Representacao_intermediaria::representar_acesso_de_variavel(No_arv_parse *nodo)
{}
void Representacao_intermediaria::representar_acesso_de_constante(No_arv_parse *nodo)
{}
void Representacao_intermediaria::representar_operacao_binaria(No_arv_parse *nodo)
{}