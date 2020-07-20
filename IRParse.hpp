#ifndef _IRPARSE_HPP_
#define _IRPARSE_HPP_
#include "ArvoreTipada.hpp"
#include "IntermedRepresentation.hpp"

class IRParse {
    public:
        Exp_ir* extrai_exp(Exp *exp);
        ExpList* extrai_lista_de_expressoes(ListaExpressoes *explist);
        Stm_ir* extrai_comando(Comando *command);
        Stm_ir* extrai_funcao(Funcao *function);
        ExpList* extrai_lista_de_declaracoes(ListaDeclaracao *declist);
        Stm_ir* extrai_lista_de_comandos(ListaComandos *commands);
};

#endif