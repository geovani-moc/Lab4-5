#include "IRParse.hpp"

class Exp;

Exp_ir* IRParse::extrai_exp(Exp *exp, Frame *frame){
    cerr << "adicionou nó equivalente a " << exp->TypeClass() << endl;
    if(exp->TypeClass().compare("ExpID") == 0) {
        cerr << "AcessouX ID [" <<((ID*)((ExpID*)exp)->id)->nome << "] na posição [" << frame->get_posicao(((ID*)((ExpID*)exp)->id)->nome)<< "]. frame = "<< frame->get_posicao_frame_pointer_anterior()<<endl;
        return new Mem( new Binop(  "+", // aqui sempre será feita uma soma do FP com o "delta a"
                                    new Temp("FP",to_string(frame->get_posicao_frame_pointer_anterior())),
                                    new Const(to_string(frame->get_posicao(((ID*)((ExpID*)exp)->id)->nome)))));
    }
    if(exp->TypeClass().compare("ExpOper") == 0) {
        return new Binop(   ((ExpOper *)exp)->operador.imagem,
                            extrai_exp(((ExpOper *)exp)->esq, frame),
                            extrai_exp(((ExpOper *)exp)->dir, frame) );
    }
    if(exp->TypeClass().compare("ExpNum") == 0) {
        return new Const( ((ExpNum *)exp)->num.imagem );
    }
    if(exp->TypeClass().compare("ExpChamada") == 0) {
        string tempName = GerarNome("temp");
        return new Eseq(new Move(new Temp("temporario",tempName),new Call( new Name( new Label(((ExpChamada *)exp)->nome_funcao_chamada->nome)),
                         new ExpList( extrai_exp(((ExpChamada *)exp)->lista_exp->exp, frame),
                                      extrai_lista_de_expressoes( ((ExpChamada *)exp)->lista_exp->prox, frame )))), new Temp("temporario",tempName));
    }

    if (exp != NULL) {
        cerr << "não executou nenhum return ["<<exp->TypeClass()<<"][IRParse.cpp:27]" << endl;
    } else {
        cerr << "fim, NULL pointer" << endl;
    }
}




//usando a padronização do livro
Stm_ir* IRParse::extrai_comando(Comando *command, Frame *frame) {

    cout << "adicionou nó equivalente a " << command->TypeClass() << endl;

    if(command->TypeClass().compare("ComandoIF") == 0) {
        string verdadeiro = GerarNome("verdadeiro");
        string depois = GerarNome("depois");        
        return new Seq(new Cjump(   ((ExpOper*)((ComandoIF *)command)->cond)->operador.imagem,
                                    extrai_exp(((ExpOper*)((ComandoIF *)command)->cond)->esq, frame),
                                    extrai_exp(((ExpOper*)((ComandoIF *)command)->cond)->dir, frame),
                                    new Label(verdadeiro),
                                    new Label(depois) ),
                        new Seq( new Seq( new Label(verdadeiro), extrai_comando( ((ComandoIF *)command)->com, frame) ), new Label(depois)));
    }

    if(command->TypeClass().compare("ComandoAtrib") == 0) {
        cerr << "Acessou ID [" <<((ID*)((ComandoAtrib*)command)->id)->nome << "] na posição [" << frame->get_posicao(((ID*)((ComandoAtrib*)command)->id)->nome)<< "]. frame = "<< frame->get_posicao_frame_pointer_anterior()<<endl;
        return new Move( new Mem(new Binop( "+", // aqui sempre será feita uma soma do FP com o "delta a"
                                            new Temp("FP",to_string(frame->get_posicao_frame_pointer_anterior())),
                                            new Const(to_string(frame->get_posicao(((ID*)((ComandoAtrib*)command)->id)->nome))))),
                        extrai_exp( ((ComandoAtrib*)command)->exp, frame) );
    }

    if(command->TypeClass().compare("ComandoBloco") == 0) {
        extrai_lista_de_declaracoes(((ComandoBloco*)command)->bloco->lista_dec, frame);
        return extrai_lista_de_comandos( ((Bloco*)((ComandoBloco*)command)->bloco)->lista_com, frame);
    }

    if(command->TypeClass().compare("ComandoWhile") == 0) {
        string inicio = GerarNome("inicio");
        string verdadeiro = GerarNome("verdadeiro");
        string falso = GerarNome("falso");
        string fim = GerarNome("fim");
        return new Seq(new Label(inicio), new Seq( new Cjump( ((ExpOper*)((ComandoWhile*)command)->cond)->operador.imagem,
                                                                extrai_exp(((ExpOper*)((ComandoWhile*)command)->cond)->esq, frame),
                                                                extrai_exp(((ExpOper*)((ComandoWhile*)command)->cond)->dir, frame),
                                                                new Label(verdadeiro),
                                                                new Label(falso)),
                                                    new Seq(new Label(verdadeiro),
                                                            new Seq(extrai_comando(((ComandoWhile*)command)->com, frame),
                                                                    new Seq(new Jump( new Name(new Label(inicio)), new LabelList(new Label(inicio),NULL)),
                                                                            new Ex(new Name(new Label(fim))))))));
    }
    if (command != NULL) {
        cerr << "não executou nenhum return ["<<command->TypeClass()<<"][IRParse.cpp:59]" << endl;
    } else {
        cerr << "fim, NULL pointer" << endl;
    } 
}

Stm_ir* IRParse::extrai_funcao(Funcao *function, Frame *frame) {
    extrai_lista_de_parametros(function->params, frame);
    extrai_lista_de_declaracoes(function->decls, frame);
    return extrai_lista_de_comandos(function->coms, frame);
    //return new Eseq(new Move(   new Temp("temp","r1"),
    //                            Call(new Name( new Label(function->ident_funcao->nome)),extrai_lista_de_declaracoes(function->decls))),
    //                new Temp("temp","r1"));
}

Stm_ir* IRParse::extrai_lista_de_comandos(ListaComandos *commands, Frame *frame) {
    if(commands != NULL) {
        return new Seq(extrai_comando(commands->com, frame), extrai_lista_de_comandos(commands->prox, frame));
    }
    return NULL;
}

ExpList* IRParse::extrai_lista_de_expressoes(ListaExpressoes * explist, Frame *frame) {
    if(explist != NULL) {

        return new ExpList( extrai_exp(explist->exp, frame),
                            extrai_lista_de_expressoes(explist->prox, frame) );
    }
    return NULL;
}

IRParse::IRParse(){
    contador = 0;
}

string IRParse::GerarNome(string str) {
    return str+to_string(contador++);
}

void IRParse::extrai_lista_de_parametros(ListaParametro *paramList, Frame *frame){
    if(paramList != NULL){
        frame->AtribuiParam(paramList->dec->identif->nome);
        cout <<"Adicionado parametro ["<< paramList->dec->identif->nome << "] em [+" << to_string(frame->get_posicao(paramList->dec->identif->nome)) <<"]"<< endl;
        extrai_lista_de_parametros(paramList->prox, frame);
    }
}

void IRParse::extrai_lista_de_declaracoes(ListaDeclaracao *decList, Frame *frame) {
    if(decList != NULL) {
        frame->AtribuiID(decList->dec->identif->nome);
        cout <<"Adicionado declaracao ["<< decList->dec->identif->nome << "] em [" << to_string(frame->get_posicao(decList->dec->identif->nome)) << "]" << endl;
        extrai_lista_de_declaracoes(decList->prox, frame);
    }
}