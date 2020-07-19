#ifndef _IRPARSE_HPP_
#define _IRPARSE_HPP_
#include "ArvoreTipada.hpp"
#include "IntermedRepresentation.hpp"

class IRParse {
    public:
        Exp_ir* extrai_exp(Exp *exp);
        Seq_ir* extrai_comando(Comando *comando);
}

#endif