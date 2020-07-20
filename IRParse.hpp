#ifndef _IRPARSE_HPP_
#define _IRPARSE_HPP_
#include "ArvoreTipada.hpp"
#include "IntermedRepresentation.hpp"

class IRParse {
    public:
        Exp_ir* extrai_exp(Exp *exp);
        ExpList* extrai_lista_de_expressoes(ListaExpressoes * explist);
        Seq_ir* extrai_comando(Comando *command);
        Seq_ir* extrai_funcao(Funcao *funcao);
        //extrai_lista_de_comandos();
}

#endif