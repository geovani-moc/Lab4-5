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
    No_arvore_RI *nodo;
    int tamanho = (int)no_arvore_parse->filhos.size();
    string nome = no_arvore_parse->tok.nome;
    string operador;

    pair<string, string> valor_operador;
    pair<string, string> valor_operador2;

    No_arvore_RI *temporario;

    int caso = definir_caso(nodo->derivacao);

    switch (caso)
    {
    case NENHUM:
        for (int i = 0; i < tamanho; ++i)
        {
            if (no_arvore_parse->filhos[i]->regra != -1)
            {
                temporario = gerar_representacao(no_arvore_parse);
                if (temporario != NULL)
                    nodo->derivacao.push_back(temporario);
            }
        }
        break;

    case IF:
        break;

    case WHILE:
        break;

    case BINOP:
        break;

    case ATRIBUICAO:
        break;

    case VARIAVEL:
        nodo->representacao.first = "MEM";
        operador = "+";
        
        valor_operador.first = "temp";
        valor_operador.second = "FP";

        valor_operador2.first = "const";
        valor_operador2.second = to_string(frame.get_posicao(nome));
        
        nodo->derivacao.push_back(binop(operador, valor_operador, valor_operador2));
        break;

    case CONSTANTE:
        break;

    default:
        break;
    }

    return nodo;
}

int Arvore_RI::definir_caso(vector<No_arvore_RI *> &derivacao)
{
    if (derivacao.size() == 1)
    {
        if (derivacao[0]->representacao.first.compare("num") == 0)
            return CONSTANTE;
        if (derivacao[0]->representacao.first.compare("id") == 0)
            return VARIAVEL;
    }
    if (derivacao.size() >= 3)
    {

        if (derivacao[0]->representacao.first.compare("if") == 0)
            return IF;
        if (derivacao[0]->representacao.first.compare("while") == 0)
            return WHILE;
        if ((derivacao[0]->representacao.first.compare("id") == 0) && (derivacao[1]->representacao.first.compare("=") == 0))
            return ATRIBUICAO;
        if (derivacao[0]->representacao.first.compare("E") == 0)
        {
            if (derivacao[1]->representacao.first.compare("||"))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("&&"))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("=="))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("!="))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("<"))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("+"))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("-"))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("*"))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("/"))
                return BINOP;
            if (derivacao[1]->representacao.first.compare("%"))
                return BINOP;
        }

        if ((derivacao[0]->representacao.first.compare("id") == 0) && (derivacao[2]->representacao.first.compare("P") == 0))
            return FUNCAO;
    }

    return NENHUM;
}


No_arvore_RI* Arvore_RI::binop(string &operacao, pair<string, string> operador1, pair<string, string> operador2)
{
    No_arvore_RI * novo = new No_arvore_RI;
    novo->representacao.first = "BINOP";
    
    No_arvore_RI *temporario = new No_arvore_RI;
    temporario->representacao.first = operacao;
    novo->derivacao.push_back(temporario);

    temporario = new No_arvore_RI;
    temporario->representacao = operador1;
    novo->derivacao.push_back(temporario);

    temporario = new No_arvore_RI;
    temporario->representacao = operador2;
    novo->derivacao.push_back(temporario);

    return novo;
}
