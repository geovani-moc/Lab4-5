#include "IntermedRepresentation.hpp"

ExpList::ExpList(Exp_ir *h, ExpList *t): head(h), tail(t) {}
StmList::StmList(Stm_ir *h, StmList *t): head(h), tail(t) {}
Label::Label(string l): label(l) {}
Const::Const(string v): value(v) {}
Name::Name(Label *l): label(l) {}
Temp::Temp(string t, string v): temp(t), value(v) {}
Binop::Binop(string o, Exp_ir*l, Exp_ir*r): op(o), left(l), right(r) {}
Mem::Mem(Exp_ir*e): exp(e) {}
Call::Call(Exp_ir *f, ExpList *a): func(f), args(a) {}
Eseq::Eseq(Stm_ir *s, Exp_ir*e): stm(s), exp(e) {}
Move::Move(Exp_ir*d, Exp_ir*s): dest(d), src(s) {}
Ex::Ex(Exp_ir*e): exp(e) {}
LabelList::LabelList(Label *l, LabelList *t): label(l), tail(t) {}
Jump::Jump(Exp_ir*e, LabelList *l): exp(e), labellist(l) {}
Cjump::Cjump(string re, Exp_ir*le, Exp_ir*ri, Label *ift, Label *iff): relop(re), left(le), right(ri), iftrue(ift), iffalse(iff) {}
Seq::Seq(Stm_ir *l, Stm_ir *r): left(l), right(r) {}

string Label::TypeClass() { return "Label"; }
string Const::TypeClass() { return "Const"; }
string Name::TypeClass() { return "Name"; }
string Temp::TypeClass() { return "Temp"; }
string Binop::TypeClass() { return "Binop"; }
string Mem::TypeClass() { return "Mem"; }
string Call::TypeClass() { return "Call"; }
string Eseq::TypeClass() { return "Eseq"; }
string Move::TypeClass() { return "Move"; }
string Ex::TypeClass() { return "Ex"; }
string Jump::TypeClass() { return "Jump"; }
string Cjump::TypeClass() { return "Cjump"; }
string Seq::TypeClass() { return "Seq"; }