#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "expr.h"
#include <cstdio>
#include <memory>

class Interpreter: ExprVisitor {
private:
    double evaluate(std::shared_ptr<Expr> expr);
public:
    bool error;
    Interpreter();
    double interpret(std::shared_ptr<Expr> expression);
    virtual double visit_binary(std::shared_ptr<Binary> expr) override;
    virtual double visit_grouping(std::shared_ptr<Grouping> expr) override;
    virtual double visit_literal(std::shared_ptr<Literal> expr) override;
};

#endif
