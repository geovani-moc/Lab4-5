#include "Frame.hpp"

Frame::Frame(Arvore_parse &arvore)
{
    posicoes_das_variaveis = identificar_variaveis(arvore);
    posicoes_dos_parametros = identificar_parametros(arvore);
    tamanho_frame = calcula_tamanho_do_frame();
}

int Frame::calcula_tamanho_do_frame()
{
    tamanho_frame = 8 * (int)(3 + posicoes_das_variaveis.size() + posicoes_dos_parametros.size());
}

int Frame::get_tamanho_do_frame() { return tamanho_frame; }

int Frame::get_posicao_frame_anterior() { return posicao_frame_anterior; }

int Frame::get_posicao_endereco_retorno() { return posicao_endereco_de_retorno; }

int Frame::get_posicao_valor_de_retorno() { return posicao_valor_de_retorno; }

int Frame::get_posicao(string &nome)
{
    int tamanho = posicoes_das_variaveis.size();
    for (int i = 0; i < tamanho; i++)
    {
        if(posicoes_das_variaveis[i].first == nome) return posicoes_das_variaveis[i].second;
    }

    tamanho = posicoes_dos_parametros.size();
    for (int i = 0; i < tamanho; i++)
    {
        if(posicoes_dos_parametros[i].first == nome) return posicoes_dos_parametros[i].second;
    }

    cerr << "\nErro: varivavel ou parametro nao encontrada no frame." << endl;
    exit(EXIT_FAILURE);
}

vector<pair<string, int>> identificar_variaveis(Arvore_parse &arvore)
{
    //No_arv_parse raiz = arvore.raiz;
}

vector<pair<string, int>> identificar_parametros(Arvore_parse &arvore)
{
}
