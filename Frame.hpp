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
    pair<int, int*> posicao_frame_pointer_anterior;
    pair<int, int*> posicao_endereco_de_retorno;

    vector<tuple<string, int, int*>> posicoes_das_variaveis;
    vector<tuple<string, int, int*>> posicoes_dos_parametros;

    pair<int, int*> posicao_valor_de_retorno;
    int tamanho_frame;

    int calcula_tamanho_do_frame();

    vector<tuple<string, int, int*>> identificar_variaveis(Arvore_parse &arvore);
    void identificar_variaveis(No_arv_parse *no_arvore, vector<tuple<string, int, int*>> &variaveis);

    vector<tuple<string, int, int*>> identificar_parametros(Arvore_parse &arvore);
    void identificar_parametros(No_arv_parse *no_arvore, vector<tuple<string, int, int*>> &parametros);

public:
    Frame(Arvore_parse &arvore);
    ~Frame();
    int get_tamanho_do_frame();
    int get_posicao_frame_pointer_anterior();
    int get_posicao_endereco_retorno();
    int get_posicao_valor_de_retorno();
    int get_posicao(string &nome);
};

#endif