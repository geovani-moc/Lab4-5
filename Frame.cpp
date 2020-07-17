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

int Frame::get_tamanho_do_frame(){return tamanho_frame;}

int Frame::get_posicao_frame_anterior(){return posicao_frame_anterior;}

int Frame::get_posicao_endereco_retorno(){return posicao_endereco_de_retorno;}

int Frame::get_posicao_valor_de_retorno(){return posicao_valor_de_retorno;}

int Frame::get_posicao_variavel()
{
    
}

int Frame::get_posicao_parametro()
{

}

