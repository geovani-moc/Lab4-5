#include "RepresentacaoIntermediaria.hpp"

No_arvore_RI::No_arvore_RI()
{
}

Arvore_RI::Arvore_RI(Arvore_parse &arvore_parse)
{
    frame = Frame(arvore_parse);
    raiz = NULL;
    contador_names = 0;

    gerar_representacao(arvore_parse); // tem que começar com um seq
}

void Arvore_RI::gerar_representacao(Arvore_parse &arvore_parse)
{
    raiz = new No_arvore_RI;

    raiz->representacao.first = "SEQ";
    raiz->representacao.second = ""; //colocar "seq"

    //adicionar um SEQ para W e return E

    raiz->derivacao.push_back(gerar_representacao(arvore_parse.raiz->filhos[7])); // tem que começar com um seq
    raiz->derivacao.push_back(gerar_representacao(arvore_parse.raiz->filhos[9]));
}

No_arvore_RI *Arvore_RI::gerar_representacao(No_arv_parse *no_arvore_parse)
{
    No_arvore_RI *novo = NULL;
    int tamanho = (int)no_arvore_parse->filhos.size();
    string nome = no_arvore_parse->tok.nome;

    No_arvore_RI *temporario;

    int caso = definir_caso(no_arvore_parse->regra);

    switch (caso)
    {
    case NENHUM:
        for (int i = 0; i < tamanho; ++i)
        {
            if (no_arvore_parse->filhos[i]->regra != -1)
            {
                temporario = gerar_representacao(no_arvore_parse);
                if (temporario != NULL) novo->derivacao.push_back(temporario);
            }
        }
        break;

    case IF:
        break;

    case WHILE:
        break;

    case BINOP:// tem que refazer
        novo = new No_arvore_RI;

        novo = binop(no_arvore_parse->filhos[2]->tok.nome, 
            gerar_representacao(no_arvore_parse->filhos[0]), 
            gerar_representacao(no_arvore_parse->filhos[2]));
        break;

    case ATRIBUICAO:
        novo = new No_arvore_RI;

        novo->representacao.first = "MOVE";
        novo->derivacao.push_back(variavel(no_arvore_parse->filhos[0]));
        novo->derivacao.push_back(
            gerar_representacao(no_arvore_parse->filhos[2])
        );

        break;

    case VARIAVEL:// tem que refazer
        novo = new No_arvore_RI;
        novo->representacao.first = "MEM";
        //operador = "+";

       /* nodo->derivacao.push_back(
            binop(operador, 
            valor_operador, 
            valor_operador2));*/
        break;

    case CONSTANTE:
        novo = new No_arvore_RI;
        novo->representacao.first = "const";
        novo->representacao.second = no_arvore_parse->tok.imagem;      
        break;

    default:
        break;
    }

    return novo;
}

int Arvore_RI::definir_caso(int regra)
{
    switch (regra)
    {
    case 11: return ATRIBUICAO;
    case 12: return IF;
    case 13: return WHILE;
    case 14 ... 23: return BINOP;
    case 25: return VARIAVEL;
    case 26: return CONSTANTE;
    case 27: return FUNCAO;
    default: break;
    }

    return NENHUM;
}

No_arvore_RI *Arvore_RI::binop(string &operacao, No_arvore_RI *no1, No_arvore_RI *no2)
{   
    No_arvore_RI *novo = new No_arvore_RI;
    novo->representacao.first = "BINOP";

    No_arvore_RI *temporario = new No_arvore_RI;
    temporario->representacao.first = operacao;

    novo->derivacao.push_back(temporario);
    novo->derivacao.push_back(no1);
    novo->derivacao.push_back(no2);

    return novo;
}

No_arvore_RI * Arvore_RI::variavel(No_arv_parse *no)
{
    No_arvore_RI *novo;

    return novo;
}
