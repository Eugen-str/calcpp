#include "interpreter.h"

Interpreter::Interpreter(){
    error = false;
}

double Interpreter::evaluate(std::shared_ptr<Expr> expr){
    return expr->accept(*this);
}

double Interpreter::interpret(std::shared_ptr<Expr> expression){
    return evaluate(expression);
}

double Interpreter::visit_binary(std::shared_ptr<Binary> expr) {
    double left = evaluate(expr->left);
    double right = evaluate(expr->right);

    switch(expr->op.type) {
        case MINUS:
            return left - right;
        case PLUS:
            return left + right;
        case STAR:
            return left * right;
        case SLASH:
            return left / right;
        default:
            error = true;
            printf("ERROR: Unexpected error in interpreter\n");
    }

    error = true;
    printf("ERROR: Unreachable code in interpreter\n");
    return -1;
}

double Interpreter::visit_grouping(std::shared_ptr<Grouping> expr) {
    return evaluate(expr->expression);
}

double Interpreter::visit_literal(std::shared_ptr<Literal> expr) {
    return expr->value;
}

