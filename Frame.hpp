#ifndef FRAME_HPP
#define FRAME_HPP

#include <vector>
#include <utility>
#include <string>
#include <tuple>

#include "Arvore.hpp"

class Frame
{
private://posicoes definidas em relacao ao stack pointer
    int frame_pointer_anterior;
    int endereco_de_retorno;

    vector<tuple<string, int>> variaveis;
    vector<tuple<string, int>> parametros;

    int valor_de_retorno;
    int tamanho_frame;

    int calcula_tamanho_do_frame();

    void identificar_variaveis(Arvore_parse &arvore);
    void identificar_variaveis(No_arv_parse *no_arvore);

    void identificar_parametros(Arvore_parse &arvore);
    void identificar_parametros(No_arv_parse *no_arvore);

public:
    Frame();
    Frame(Arvore_parse &arvore);
    int get_tamanho_do_frame();
    int get_posicao_frame_pointer_anterior();
    int get_posicao_endereco_retorno();
    int get_posicao_valor_de_retorno();
    int get_posicao(string &nome);
};

#endif