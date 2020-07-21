#include "RepresentacaoIntermediaria.hpp"

No_arvore_RI::No_arvore_RI()
{
}

Arvore_RI::Arvore_RI(Arvore_parse &arvore_parse)
{
    frame = Frame(arvore_parse);
    raiz = NULL; //olhar se e necessario adicionar um seq aqui
    contador_names = 0;
    gerar_representacao(arvore_parse.raiz);
}

No_arvore_RI* Arvore_RI::gerar_representacao(No_arv_parse *no_arvore_parse)
{
    int tamanho = (int)no_arvore_parse->filhos.size();

    for (size_t i = 0; i < tamanho; ++i)
    {
        if(no_arvore_parse->filhos[i]->regra != -1) return gerar_representacao(no_arvore_parse);
    }
    
}