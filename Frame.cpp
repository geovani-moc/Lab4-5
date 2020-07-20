#include "Frame.hpp"

Frame::Frame(Arvore_parse &arvore)
{
    endereco_de_retorno.first = 0;
    frame_pointer_anterior.first = -8;
    identificar_variaveis(arvore);
    identificar_parametros(arvore);
    valor_de_retorno.first = ((int)(variaveis.size() + parametros.size() + 2)) * (-8);

    tamanho_frame = calcula_tamanho_do_frame();
}

Frame::~Frame(){
    int tamanho;
}

int Frame::calcula_tamanho_do_frame()
{
    return 8 * (int)(3 + variaveis.size() + parametros.size());
}

int Frame::get_tamanho_do_frame() { return tamanho_frame; }

int Frame::get_posicao_frame_pointer_anterior() { return frame_pointer_anterior.first; }

int Frame::get_posicao_endereco_retorno() { return endereco_de_retorno.first; }

int Frame::get_posicao_valor_de_retorno() { return valor_de_retorno.first; }

int Frame::get_posicao(string &nome)
{
    int tamanho = variaveis.size();
    for (int i = 0; i < tamanho; i++)
    {
        if (get<0>(variaveis[i]) == nome)
            return get<1>(variaveis[i]);
    }

    tamanho = parametros.size();
    for (int i = 0; i < tamanho; i++)
    {
        if (get<0>(parametros[i]) == nome)
            return get<1>(parametros[i]);
    }

    cerr << "\nErro: varivavel ou parametro nao encontrada no frame." << endl;
    exit(EXIT_FAILURE);
}

void Frame::identificar_variaveis(Arvore_parse &arvore)
{
    No_arv_parse *raiz = arvore.raiz;

    int quantidade_filhos = (int)raiz->filhos.size();

    for (int i = 6; i < quantidade_filhos; ++i)
    {
        if (raiz->filhos[i]->regra != -1)
        {
            identificar_variaveis(raiz->filhos[i]);
        }
    }
}

void Frame::identificar_variaveis(No_arv_parse *no_arvore)
{
    if (no_arvore->tok.nome.compare("D") == 0)
    {
        tuple<string, int, int *> temporario;
        get<0>(temporario) = no_arvore->filhos[1]->tok.imagem;
        get<1>(temporario) = (-16) - (8 * (int)variaveis.size());
        get<2>(temporario) = (int *)malloc(sizeof(int));

        variaveis.push_back(temporario);
    }
    int tamanho = (int)no_arvore->filhos.size();

    for (int i = 0; i < tamanho; ++i)
    {
        if (no_arvore->filhos[i]->regra != -1)
        {
            identificar_variaveis(no_arvore->filhos[i]);
        }
    }
}

void Frame::identificar_parametros(Arvore_parse &arvore)
{
    vector<tuple<string, int, int *>> parametros;
    No_arv_parse *raiz = arvore.raiz;

    int quantidade_filhos = (int)raiz->filhos.size();

    for (int i = 0; i < quantidade_filhos; ++i)
    {
        if (raiz->filhos[i]->regra != -1)
        {
            identificar_parametros(raiz->filhos[i]);
        }
    }
}

void Frame::identificar_parametros(No_arv_parse *no_arvore)
{
    if (no_arvore->tok.nome.compare("P") == 0)
    {
        tuple<string, int, int *> temporario;
        get<0>(temporario) = "parametro" + to_string(parametros.size());
        get<1>(temporario) = (-16) - (8 * ((int)parametros.size() + variaveis.size()));
        get<2>(temporario) = (int *)malloc(sizeof(int));

        parametros.push_back(temporario);
    }
    int tamanho = (int)no_arvore->filhos.size();

    for (int i = 0; i < tamanho; ++i)
    {
        if (no_arvore->filhos[i]->regra != -1)
        {
            identificar_parametros(no_arvore->filhos[i]);
        }
    }
}
