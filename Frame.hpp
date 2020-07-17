#ifndef FRAME_HPP
#define FRAME_HPP

#include <vector>
#include <map>
#include <string>

#include "Arvore.hpp"

class Frame
{
private://posicoes definidas em relacao ao stack pointer
    int posicao_frame_anterior;
    int posicao_endereco_de_retorno;
    vector<map<string, int>> posicoes_das_variaveis;
    vector<map<string, int>> posicoes_dos_parametros;
    int posicao_valor_de_retorno;

    int tamanho_frame;

    int calcula_tamanho_do_frame();
    vector<map<string, int>> identificar_variaveis(Arvore_parse &arvore);
    vector<map<string, int>> identificar_parametros(Arvore_parse &arvore);

public:
    Frame(Arvore_parse &arvore);
    ~Frame();
    int get_tamanho_do_frame();
    int get_posicao_frame_anterior();
    int get_posicao_endereco_retorno();
    int get_posicao_variavel();
    int get_posicao_parametro();
    int get_posicao_valor_de_retorno();
};

#endif