#ifndef REPRESENTACAO_INTERMEDIARIA_HPP
#define REPRESENTACAO_INTERMEDIARIA_HPP

#include <string>

#include "Arvore.hpp"
#include "Frame.hpp"

#define IF (1)
#define WHILE (2)
#define ATRIBUICAO (3)
#define CHAMADA_DE_FUNCAO (4)
#define ACESSO_DE_VARIAVEL (5)
#define ACESSO_DE_CONSTANTE (6)
#define OPERACAO_BINARIA (7)

using namespace std;

class Representacao_intermediaria
{
private:
    string representacao_intermediaria;
    Frame frame;

    void criar_representacao(Arvore_parse &arvore);
    void criar_representacao(No_arv_parse *nodo);
    int identifica_caso(No_arv_parse *nodo);

    void representar_if(No_arv_parse *condicao, No_arv_parse *bloco);
    void representar_while(No_arv_parse *condicao, No_arv_parse *bloco);
    void representar_atribuicao(No_arv_parse *nodo);
    void representar_chamada_de_funcao(No_arv_parse *nodo);
    void representar_acesso_de_variavel(No_arv_parse *nodo);
    void representar_acesso_de_constante(No_arv_parse *nodo);
    void representar_operacao_binaria(No_arv_parse *nodo);

public:
    Representacao_intermediaria(Arvore_parse &arvore);
    ~Representacao_intermediaria();

    string get_representaocao_intermediaria();
};

#endif