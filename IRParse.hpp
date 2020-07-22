#ifndef _IRPARSE_HPP_
#define _IRPARSE_HPP_
#include "ArvoreTipada.hpp"
#include "IntermedRepresentation.hpp"
#include "Frame.hpp"
#include <iostream>

using namespace std;

class IRParse {
    private:
        int contador;
        string GerarNome(string str);
    public:
        Exp_ir* extrai_exp(Exp *exp, Frame *frame);
        ExpList* extrai_lista_de_expressoes(ListaExpressoes *explist, Frame *frame);
        Stm_ir* extrai_comando(Comando *command, Frame *frame);
        Stm_ir* extrai_funcao(Funcao *function, Frame *frame);
        Stm_ir* extrai_lista_de_comandos(ListaComandos *commands, Frame *frame);
        void extrai_lista_de_declaracoes(ListaDeclaracao *decList, Frame *frame);
        void extrai_lista_de_parametros(ListaParametro *paramList, Frame *frame);
        void imprime(Exp_ir* exp, Stm_ir *stm, ExpList *expList, StmList *stmList);
        IRParse();
};

#endif