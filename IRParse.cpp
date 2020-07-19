#include "IRParse.hpp"

Mem* IRParse::extrai_id(ID *id){
    return new Mem( new Binop(BINOP_PLUS,
                    new Temp("FP",/*Valor de FP*/),
                    new Const(/*número do id da tabela do lab4*/)));
}


