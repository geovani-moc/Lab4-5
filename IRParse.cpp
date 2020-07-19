#include "IRParse.hpp"

class Exp;

Exp_ir* IRParse::extrai_exp(Exp *exp){
    if(exp->TypeClass().compare("ExpID") == 0) {
        return new Mem( new Binop(  "+", // aqui sempre será feita uma soma do FP com o "delta a"
                                    new Temp("FP",/*Valor de FP*/),
                                    new Const(/*número do id da tabela do lab4*/)));
    }

    if(exp->TypeClass().compare("ExpOper") == 0) {
        return new Binop(   ((ExpOper *)exp)->operador.nome,
                            extrai_exp(((ExpOper *)exp)->esq),
                            extrai_exp(((ExpOper *)exp)->dir) );
    }
}



//Seq* IRParse::extrai_comando(Comando *comando) {
//    if(comando->TypeClass().compare("ComandoIF") == 0) {
//        return new Seq(new Cjump(/*E*/, new Label()), new Seq())
//    }
//}


