#include "IRParse.hpp"

class Exp;

Exp_ir* IRParse::extrai_exp(Exp *exp){
    cout << "adicionou nó equivalente a " << exp->TypeClass() << endl;
    if(exp->TypeClass().compare("ExpID") == 0) {
        return new Mem( new Binop(  "+", // aqui sempre será feita uma soma do FP com o "delta a"
                                    new Temp("FP",/*Valor de FP (string)*/"00"),
                                    new Const(/*número do id da tabela do lab4*/"12")));
    }
    if(exp->TypeClass().compare("ExpOper") == 0) {
        return new Binop(   ((ExpOper *)exp)->operador.imagem,
                            extrai_exp(((ExpOper *)exp)->esq),
                            extrai_exp(((ExpOper *)exp)->dir) );
    }
    if(exp->TypeClass().compare("ExpNum") == 0) {
        return new Const( ((ExpNum *)exp)->num.imagem );
    }
    if(exp->TypeClass().compare("ExpChamada") == 0) {
        string tempName = GerarNome("temp");
        return new Eseq(new Move(new Temp("temporario",tempName),new Call( new Name( new Label(((ExpChamada *)exp)->nome_funcao_chamada->nome)),
                         new ExpList( extrai_exp(((ExpChamada *)exp)->lista_exp->exp),
                                      extrai_lista_de_expressoes( ((ExpChamada *)exp)->lista_exp->prox )))), new Temp("temporario",tempName));
    }

    if (exp != NULL) {
        cerr << "não executou nenhum return ["<<exp->TypeClass()<<"][IRParse.cpp:27]" << endl;
    } else {
        cerr << "fim, NULL pointer" << endl;
    }
}



/*ExpList* IRParse::extrai_lista_de_declaracoes(ListaDeclaracao * declist) {
    if(declist != NULL) {
        return new ExpList( extrai_exp(declist->dec),
                            extrai_lista_de_declaracoes(declist->prox) );
    }
    return NULL;
}*/

//usando a padronização do livro
Stm_ir* IRParse::extrai_comando(Comando *command) {

    cout << "adicionou nó equivalente a " << command->TypeClass() << endl;

    if(command->TypeClass().compare("ComandoIF") == 0) {
        string verdadeiro = GerarNome("verdadeiro");
        string depois = GerarNome("depois");        
        return new Seq(new Cjump(   ((ExpOper*)((ComandoIF *)command)->cond)->operador.imagem,
                                    extrai_exp(((ExpOper*)((ComandoIF *)command)->cond)->esq),
                                    extrai_exp(((ExpOper*)((ComandoIF *)command)->cond)->dir),
                                    new Label(verdadeiro),
                                    new Label(depois) ),
                        new Seq( new Seq( new Label(verdadeiro), extrai_comando( ((ComandoIF *)command)->com) ), new Label(depois)));
    }

    if(command->TypeClass().compare("ComandoAtrib") == 0) {
        return new Move( new Mem(new Binop( "+", // aqui sempre será feita uma soma do FP com o "delta a"
                                            new Temp("FP",/*Valor de FP (string)*/"teste"),
                                            new Const(/*número do id da tabela do lab4*/"12"))),
                        extrai_exp( ((ComandoAtrib*)command)->exp) );
    }

    if(command->TypeClass().compare("ComandoBloco") == 0) {
        return extrai_lista_de_comandos( ((Bloco*)((ComandoBloco*)command)->bloco)->lista_com);
    }

    if(command->TypeClass().compare("ComandoWhile") == 0) {
        string inicio = GerarNome("inicio");
        string verdadeiro = GerarNome("verdadeiro");
        string falso = GerarNome("falso");
        string fim = GerarNome("fim");
        return new Seq(new Label(inicio), new Seq( new Cjump( ((ExpOper*)((ComandoWhile*)command)->cond)->operador.imagem,
                                                                extrai_exp(((ExpOper*)((ComandoWhile*)command)->cond)->esq),
                                                                extrai_exp(((ExpOper*)((ComandoWhile*)command)->cond)->dir),
                                                                new Label(verdadeiro),
                                                                new Label(falso)),
                                                    new Seq(new Label(verdadeiro),
                                                            new Seq(extrai_comando(((ComandoWhile*)command)->com),
                                                                    new Seq(new Jump( new Name(new Label(inicio)), new LabelList(new Label(inicio),NULL)),
                                                                            new Ex(new Name(new Label(fim))))))));
    }
    if (command != NULL) {
        cerr << "não executou nenhum return ["<<command->TypeClass()<<"][IRParse.cpp:59]" << endl;
    } else {
        cerr << "fim, NULL pointer" << endl;
    } 
}

Stm_ir* IRParse::extrai_funcao(Funcao *function) {
    return extrai_lista_de_comandos(function->coms);
    //return new Eseq(new Move(   new Temp("temp","r1"),
    //                            Call(new Name( new Label(function->ident_funcao->nome)),extrai_lista_de_declaracoes(function->decls))),
    //                new Temp("temp","r1"));
}

Stm_ir* IRParse::extrai_lista_de_comandos(ListaComandos *commands) {
    if(commands != NULL) {
        return new Seq(extrai_comando(commands->com), extrai_lista_de_comandos(commands->prox));
    }
    return NULL;
}

ExpList* IRParse::extrai_lista_de_expressoes(ListaExpressoes * explist) {
    if(explist != NULL) {
        return new ExpList( extrai_exp(explist->exp),
                            extrai_lista_de_expressoes(explist->prox) );
    }
    return NULL;
}

IRParse::IRParse(){
    contador = 0;
}

string IRParse::GerarNome(string str) {
    return str+to_string(contador++);
}