#ifndef _INTERMEDREPRESENTATION_HPP_
#define _INTERMEDREPRESENTATION_HPP_
#include <string>

#define BINOP_PLUS 0
#define BINOP_MINUS 1
#define BINOP_MUL 2
#define BINOP_DIV 3
#define BINOP_AND 4
#define BINOP_OR 5
#define BINOP_LSHIFT 6
#define BINOP_RSHIFT 6
#define BINOP_ARSHIFT 8
#define BINOP_XOR 9
#define BINOP_LSHIFT 10

using namespace std;

class Exp {};
class Stm {};

class Explist {
    public:
        Exp *head;
        Explist *tail;
        Explist(Exp *h, Explist *t);
};

class StmList {
    public:
        Stm *head;
        StmList *tail;
        StmList(Stm *h, Stm *t);
};

class Label: public Stm {
    public:
        string label;
        Label(string l);
};


class Const: public Exp {
    public:
        int value;
        Const(int v);
};

class Name: public Exp {
    public:
        Label *label;
        Name(Label *l);
};

class Temp: public Exp {
    public:
        string temp;
        int value;
        Temp(string t, int v);
};

class Binop: public Exp {
    public:
        int binop;
        Exp *left;
        Exp *right;
        Binop(int b, Exp *l, Exp *r);
};

class Mem: public Exp {
    public:
        Exp *exp;
        Mem(Exp *e);
};

class Call: public Exp {
    public:
        Exp *func;
        Explist *args;
        Call(Exp *f, Explist *a);
};

class Eseq: public Exp {
    public:
        Stm *stm;
        Exp *exp;
        Eseq(Stm *s, Exp *e);
};

class Move: public Stm {
    public:
        Exp* dist;
        Exp* src;
        Move(Exp *d, Exp *s);
};

class Ex: public Exp {
    public:
        Exp *exp;
        Ex(Exp *e);
};

class LabelList {
    public:
        Label *label;
        LabelList *tail;
        LabelList(Label *l, LabelList *t);
};

class Jump: public Stm {
    public:
        Exp *exp;
        LabelList *labellist;
        Jump(Exp *e, LabelList *l);
};

class Cjump: public Stm {
    public:
        int relop;
        Exp *left;
        Exp *right;
        Label *iftrue;
        Label *iffalse;
        Cjump(int re, Exp *le, Exp *ri, Label *ift, Label *iff);
};

class Seq: public Stm {
    public:
        Stm *left;
        Stm *right;
        Seq(Stm *l, Stm *r);
};

#endif