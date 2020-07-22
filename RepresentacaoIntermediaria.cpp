#include "RepresentacaoIntermediaria.hpp"

No_arvore_RI::No_arvore_RI()
{
}
No_arvore_RI::No_arvore_RI(string nome)
{
    representacao.first = nome;
    representacao.second = "";
}
No_arvore_RI::No_arvore_RI(string nome, string imagem)
{
    representacao.first = nome;
    representacao.second = imagem;
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
    case NENHUM: //revisar
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
        novo = adicionar_if(no_arvore_parse->filhos[2], no_arvore_parse->filhos[4]);
        break;

    case WHILE: 
        novo = adicionar_while(no_arvore_parse->filhos[2], no_arvore_parse->filhos[4]);
        break;

    case BINOP:
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

    case VARIAVEL:
        novo = variavel(no_arvore_parse->filhos[0]);
        break;

    case CONSTANTE:
        novo = new No_arvore_RI;
        novo->representacao.first = "const";
        novo->representacao.second = no_arvore_parse->tok.imagem;      
        break;
    
    case FUNCAO://falta fazer
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
    No_arvore_RI *novo = new No_arvore_RI;
    No_arvore_RI *no1 = new No_arvore_RI;
    No_arvore_RI *no2 = new No_arvore_RI;
    string operacao = "+";

    no1->representacao.first = "temp";
    no1->representacao.second = "FP";

    no2->representacao.first = "const";
    no2->representacao.second = to_string(frame.get_posicao(no->tok.imagem));

    novo->representacao.first = "MEM";
    novo->derivacao.push_back(binop(operacao, no1, no2));

    return novo;
}

No_arvore_RI *Arvore_RI::adicionar_if(No_arv_parse *expressao, No_arv_parse *comando)
{
    No_arvore_RI *no_seq1 = new No_arvore_RI("SEQ");
    No_arvore_RI *no_cjump = new No_arvore_RI("CJUMP");
    No_arvore_RI *no_seq2 = new No_arvore_RI("SEQ");
    No_arvore_RI *no_seq3 = new No_arvore_RI("SEQ");

    No_arvore_RI *no_label_continuar = new No_arvore_RI(
        "LABEL",
        ("label_" + to_string(contador_names))
    );
    No_arvore_RI *no_name_continuar = new No_arvore_RI(
        "NAME",
        ("name_" + to_string(contador_names++))
    );

    No_arvore_RI *no_label_depois = new No_arvore_RI(
        "LABEL",
        ("label_" + to_string(contador_names))
    );
    No_arvore_RI *no_name_depois = new No_arvore_RI(
        "LABEL",
        ("name_" + to_string(contador_names++))
    );

    no_cjump->derivacao.push_back(gerar_representacao(expressao));
    no_cjump->derivacao.push_back(no_label_continuar);
    no_cjump->derivacao.push_back(no_label_depois);

    no_seq3->derivacao.push_back(no_name_continuar);
    no_seq3->derivacao.push_back(gerar_representacao(comando));

    no_seq2->derivacao.push_back(no_seq3);
    no_seq2->derivacao.push_back(no_name_depois);

    no_seq1->derivacao.push_back(no_cjump);
    no_seq1->derivacao.push_back(no_seq2);

    return no_seq1;
}

No_arvore_RI *Arvore_RI::adicionar_while(No_arv_parse *condicao, No_arv_parse *bloco)
{
    No_arvore_RI *no_seq1 = new No_arvore_RI("SEQ");
    No_arvore_RI *no_seq2 = new No_arvore_RI("SEQ");
    No_arvore_RI *no_seq3 = new No_arvore_RI("SEQ");
    No_arvore_RI *no_seq4 = new No_arvore_RI("SEQ");
    No_arvore_RI *no_seq5 = new No_arvore_RI("SEQ");
    No_arvore_RI *no_cjump = new No_arvore_RI("CJUMP");
    No_arvore_RI *no_jump = new No_arvore_RI("JUMP");


    No_arvore_RI *no_label_teste = new No_arvore_RI(
        "LABEL",
        ("label_" + to_string(contador_names))
    );
    No_arvore_RI *no_name_teste = new No_arvore_RI(
        "NAME",
        ("name_" + to_string(contador_names++))
    );

    No_arvore_RI *no_label_continuar = new No_arvore_RI(
        "LABEL",
        ("label_" + to_string(contador_names))
    );
    No_arvore_RI *no_name_continuar = new No_arvore_RI(
        "NAME",
        ("name_" + to_string(contador_names++))
    );

    No_arvore_RI *no_label_fim = new No_arvore_RI(
        "LABEL",
        ("label_" + to_string(contador_names))
    );
    No_arvore_RI *no_name_fim = new No_arvore_RI(
        "LABEL",
        ("name_" + to_string(contador_names++))
    );

    no_cjump->derivacao.push_back(gerar_representacao(condicao));
    no_cjump->derivacao.push_back(no_label_fim);
    no_cjump->derivacao.push_back(no_label_continuar);

    no_jump->derivacao.push_back(no_name_teste);

    no_seq5->derivacao.push_back(gerar_representacao(bloco));
    no_seq5->derivacao.push_back(no_jump);

    no_seq4->derivacao.push_back(no_label_continuar);
    no_seq4->derivacao.push_back(no_seq5);

    no_seq3->derivacao.push_back(no_seq4);
    no_seq3->derivacao.push_back(no_label_fim);

    no_seq2->derivacao.push_back(no_cjump);
    no_seq2->derivacao.push_back(no_seq3);

    no_seq1->derivacao.push_back(no_label_teste);
    no_seq1->derivacao.push_back(no_seq2);

    return no_seq1;
}