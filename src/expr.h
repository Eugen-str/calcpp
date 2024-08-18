#ifndef EXPR_H_
#define EXPR_H_

#include "token.h"
#include <any>
#include <memory>

class Binary;
class Grouping;
class Literal;

class ExprVisitor {
public:
    virtual double visit_binary(std::shared_ptr<Binary> expr) = 0;
    virtual double visit_grouping(std::shared_ptr<Grouping> expr) = 0;
    virtual double visit_literal(std::shared_ptr<Literal> expr) = 0;
};

struct Expr {
    virtual double accept(ExprVisitor& visitor) = 0;
};

class Binary : public Expr, public std::enable_shared_from_this<Binary> {
public:
    Binary(std::shared_ptr<Expr> l, Token o, std::shared_ptr<Expr> r) : left{l}, op{o}, right{r}
    { }

    virtual double accept(ExprVisitor& visitor) override {
        return visitor.visit_binary(shared_from_this());
    }

    std::shared_ptr<Expr> left;
    Token op;
    std::shared_ptr<Expr> right;
};

class Grouping : public Expr, public std::enable_shared_from_this<Grouping> {
public:
    Grouping(std::shared_ptr<Expr> expr) : expression{expr}
    { }

    virtual double accept(ExprVisitor& visitor) override {
        return visitor.visit_grouping(shared_from_this());
    }

    std::shared_ptr<Expr> expression;
};

class Literal: public Expr, public std::enable_shared_from_this<Literal> {
public:
    Literal(double value) : value{value}
    { }

    virtual double accept(ExprVisitor& visitor) override {
        return visitor.visit_literal(shared_from_this());
    }

    double value;
};

#endif
