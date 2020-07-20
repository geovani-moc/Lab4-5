#include "IntermedRepresentation.hpp"

ExpList::Explist(Exp_ir*h, Exp_ir*t): head(h), tail(t) {}
StmList::StmList(Stm_ir *h, StmList *t): head(h), tail(t) {}
Label::Label(string l): label(l) {}
Const::Const(string v): value(v) {}
Name::Name(Label *l): label(l) {}
Temp::Temp(string t, string v): temp(t), value(v) {}
Binop::Binop(string b, Exp_ir*l, Exp_ir*r): binop(b), left(l), right(r) {}
Mem::Mem(Exp_ir*e): exp(e) {}
Call::Call(Exp_ir*f, Explist *a): func(f), args(a) {}
Eseq::Eseq(Stm_ir *s, Exp_ir*e): stm(s), exp(e) {}
Move::Move(Exp_ir*d, Exp_ir*s): dist(d), src(s) {}
Ex::Ex(Exp_ir*e): exp(e) {}
LabelList::LabelList(Label *l, LabelList *t): label(l), tail(t) {}
Jump::Jump(Exp_ir*e, LabelList *l): exp(e), labellist(l) {}
Cjump::Cjump(string re, Exp_ir*le, Exp_ir*ri, Label *ift, Label *iff): relop(re), left(le), right(ri), iftrue(ift), iffalse(iff) {}
Seq::Seq(Stm_ir *l, Stm_ir *r): left(l), right(r) {}