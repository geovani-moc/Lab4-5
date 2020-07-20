#include "IRParse.hpp"

class Exp;

Exp_ir* IRParse::extrai_exp(Exp *exp){
    if(exp->TypeClass().compare("ExpID") == 0) {
        return new Mem( new Binop(  "+", // aqui sempre será feita uma soma do FP com o "delta a"
                                    new Temp("FP",/*Valor de FP (string)*/),
                                    new Const(/*número do id da tabela do lab4*/)));
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
        return new Call( new Name( new Label(((ExpChamada *)exp)->nome_funcao_chamada->nome)),
                         new ExpList( extrai_exp(((ExpChamada *)exp)->lista_exp->exp),
                                      extrai_lista_de_expressoes( ((ExpChamada *)exp)->lista_exp->prox )));
    }
}

ExpList* IRParse::extrai_lista_de_expressoes(ListaExpressoes * explist) {
    if(explist != NULL) {
        return new ExpList( ((ListaExpressoes *)explist)->exp,
                            extrai_lista_de_expressoes(((ListaExpressoes *)explist)->prox));
    }
    return NULL;
}





//usando a padronização do livro
Stm_ir* IRParse::extrai_comando(Comando *command) {
    if(command->TypeClass().compare("ComandoIF") == 0) {
        return new Seq(new Cjump(   ((ExpOper*)((ComandoIF *)command)->cond)->operador.imagem,
                                    extrai_exp(((ExpOper*)((ComandoIF *)command)->cond)->esq),
                                    extrai_exp(((ExpOper*)((ComandoIF *)command)->cond)->dir),
                                    new Label(/*Definir um label para True*/ "verdade"),
                                    new Label(/*Definir um label para False*/ "depois") ),
                        new Seq( new Seq( new Label(/*label True*/"verdade"), extrai_comando( ((ComandoIF *)command)->com) ), new Label(/*label False*/"depois")));
    }

    if(command->TypeClass().compare("ComandoAtrib") == 0) {
        return new Move( new Mem(new Binop( "+", // aqui sempre será feita uma soma do FP com o "delta a"
                                            new Temp("FP",/*Valor de FP (string)*/),
                                            new Const(/*número do id da tabela do lab4*/))),
                        extrai_exp( ((ComandoAtrib*)command)->exp) );
    }

    if(command->TypeClass().compare("ComandoBloco") == 0) {
        cerr << "ComandoBloco ainda não implementado [IRParse.cpp:53]" << endl;
    }

    if(command->TypeClass().compare("ComandoWhile") == 0) {
        cerr << "ComandoWhile ainda não implementado [IRParse.cpp:57]" << endl;
    }
    cerr << "não executou nenhum return [IRParse.cpp:59]" << endl;
}

//Seq_ir* IRParse::extrai_funcao(Funcao *funcao) {
//    return new Move(new Mem( new Binop(  "+", // aqui sempre será feita uma soma do FP com o "delta a"
//                                    new Temp("FP",/*Valor de FP (string)*/),
//                                    new Const(/*número do retorno da tabela do lab4*/))),Call(extrai_exp(funcao->coms),/*extrai_declaracoes*/funcao->decls));
//}

