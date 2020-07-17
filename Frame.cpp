#include "Frame.hpp"

Frame::Frame(Arvore_parse &arvore)
{
    posicao_endereco_de_retorno.first = 0;
    posicao_frame_pointer_anterior.first = -8;
    posicoes_das_variaveis = identificar_variaveis(arvore);
    posicoes_dos_parametros = identificar_parametros(arvore);
    posicao_valor_de_retorno.first = ((int)(posicoes_das_variaveis.size() + posicoes_dos_parametros.size()+2)) * (-8);

    tamanho_frame = calcula_tamanho_do_frame();
}

int Frame::calcula_tamanho_do_frame()
{
    return 8 * (int)(3 + posicoes_das_variaveis.size() + posicoes_dos_parametros.size());
}

int Frame::get_tamanho_do_frame() { return tamanho_frame; }

int Frame::get_posicao_frame_pointer_anterior() { return posicao_frame_pointer_anterior.first; }

int Frame::get_posicao_endereco_retorno() { return posicao_endereco_de_retorno.first; }

int Frame::get_posicao_valor_de_retorno() { return posicao_valor_de_retorno.first; }

int Frame::get_posicao(string &nome)
{
    int tamanho = posicoes_das_variaveis.size();
    for (int i = 0; i < tamanho; i++)
    {
        if (get<0>(posicoes_das_variaveis[i]) == nome)
            return get<1>(posicoes_das_variaveis[i]);
    }

    tamanho = posicoes_dos_parametros.size();
    for (int i = 0; i < tamanho; i++)
    {
        if (get<0>(posicoes_dos_parametros[i]) == nome)
            return get<1>(posicoes_dos_parametros[i]);
    }

    cerr << "\nErro: varivavel ou parametro nao encontrada no frame." << endl;
    exit(EXIT_FAILURE);
}

vector<tuple<string, int, int*>> Frame::identificar_variaveis(Arvore_parse &arvore)
{
    //No_arv_parse raiz = arvore.raiz;
    vector<tuple<string, int, int*>> variaveis;

    return variaveis;
}

vector<tuple<string, int, int*>> Frame::identificar_parametros(Arvore_parse &arvore)
{
    vector<tuple<string, int, int*>> parametros;

    return parametros;
}
