#ifndef FRAME_HPP
#define FRAME_HPP

#include <vector>
#include <utility>
#include <string>

#include "Arvore.hpp"

class Frame
{
private://posicoes definidas em relacao ao stack pointer
    int posicao_frame_anterior;
    int posicao_endereco_de_retorno;
    vector<pair<string, int>> posicoes_das_variaveis;
    vector<pair<string, int>> posicoes_dos_parametros;
    int posicao_valor_de_retorno;

    int tamanho_frame;

    int calcula_tamanho_do_frame();
    vector<pair<string, int>> identificar_variaveis(Arvore_parse &arvore);
    vector<pair<string, int>> identificar_parametros(Arvore_parse &arvore);

public:
    Frame(Arvore_parse &arvore);
    ~Frame();
    int get_tamanho_do_frame();
    int get_posicao_frame_anterior();
    int get_posicao_endereco_retorno();
    int get_posicao_valor_de_retorno();
    int get_posicao(string &nome);
};

#endif