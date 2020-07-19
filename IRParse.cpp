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
        return new Call( new Name( ((ExpChamada *)exp)->nome_funcao_chamada->nome),
                         new ExpList( extrai_exp(((ExpChamada *)exp)->lista_exp->exp),
                                      new extrai_lista_de_expressoes( ((ExpChamada *)exp)->lista_exp->prox )));
    }

    /*ExpList* extrai_lista_de_expressoes(ListaExpressoes * le)*/
}



//Seq* IRParse::extrai_comando(Comando *comando) {
//    if(comando->TypeClass().compare("ComandoIF") == 0) {
//        return new Seq(new Cjump(/*E*/, new Label()), new Seq())
//    }
//}


