#ifndef _INTERMEDREPRESENTATION_HPP_
#define _INTERMEDREPRESENTATION_HPP_
#include <string>

using namespace std;

class Exp_ir {};
class Stm_ir {};

class ExpList {
    public:
        Exp_ir *head;
        ExpList *tail;
        ExpList(Exp_ir *h, ExpList *t);
};

class StmList {
    public:
        Stm_ir *head;
        StmList *tail;
        StmList(Stm_ir *h, StmList *t);
};

class Label: public Stm_ir {
    public:
        string label;
        Label(string l);
};


class Const: public Exp_ir {
    public:
        string value;
        Const(string v);
};

class Name: public Exp_ir {
    public:
        Label *label;
        Name(Label *l);
};

class Temp: public Exp_ir {
    public:
        string temp;
        string value;
        Temp(string t, string v);
};

class Binop: public Exp_ir {
    public:
        string binop;
        Exp_ir *left;
        Exp_ir *right;
        Binop(string b, Exp_ir *l, Exp_ir *r);
};

class Mem: public Exp_ir {
    public:
        Exp_ir *exp;
        Mem(Exp_ir *e);
};

class Call: public Exp_ir {
    public:
        Exp_ir *func;
        ExpList *args;
        Call(Exp_ir *f, ExpList *a);
};

class Eseq: public Exp_ir {
    public:
        Stm_ir *stm;
        Exp_ir *exp;
        Eseq(Stm_ir *s, Exp_ir *e);
};

class Move: public Stm_ir {
    public:
        Exp_ir *dist;
        Exp_ir *src;
        Move(Exp_ir *d, Exp_ir *s);
};

class Ex: public Exp_ir {
    public:
        Exp_ir *exp;
        Ex(Exp_ir *e);
};

class LabelList {
    public:
        Label *label;
        LabelList *tail;
        LabelList(Label *l, LabelList *t);
};

class Jump: public Stm_ir {
    public:
        Exp_ir *exp;
        LabelList *labellist;
        Jump(Exp_ir *e, LabelList *l);
};

class Cjump: public Stm_ir {
    public:
        string relop;
        Exp_ir *left;
        Exp_ir *right;
        Label *iftrue;
        Label *iffalse;
        Cjump(string re, Exp_ir *le, Exp_ir *ri, Label *ift, Label *iff);
};

class Seq: public Stm_ir {
    public:
        Stm_ir *left;
        Stm_ir *right;
        Seq(Stm_ir *l, Stm_ir *r);
};

#endif