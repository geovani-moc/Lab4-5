#include "IntermedRepresentation.hpp"

Explist::Explist(Exp *h, Exp *t): head(h), tail(t) {}
StmList::StmList(Stm *h, StmList *t): head(h), tail(t) {}
Label::Label(string l): label(l) {}
Const::Const(int v): value(v) {}
Name::Name(Label *l): label(l) {}
Temp::Temp(string t, int v): temp(t), value(v) {}
Binop::Binop(int b, Exp *l, Exp *r): binop(b), left(l), right(r) {}
Mem::Mem(Exp *e): exp(e) {}
Call::Call(Exp *f, Explist *a): func(f), args(a) {}
Eseq::Eseq(Stm *s, Exp *e): stm(s), exp(e) {}
Move::Move(Exp *d, Exp *s): dist(d), src(s) {}
Ex::Ex(Exp *e): exp(e) {}
LabelList::LabelList(Label *l, LabelList *t): label(l), tail(t) {}
Jump::Jump(Exp *e, LabelList *l): exp(e), labellist(l) {}
Cjump::Cjump(int re, Exp *le, Exp *ri, Label *ift, Label *iff): relop(re), left(le), right(ri), iftrue(ift), iffalse(iff) {}
Seq::Seq(Stm *l, Stm *r): left(l), right(r) {}