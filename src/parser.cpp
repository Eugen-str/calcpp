#include "parser.h"
#include "expr.h"
#include "token.h"
#include <cstdio>
#include <memory>

Parser::Parser(std::vector<Token> tokens){
    this->tokens = tokens;
    this->current = 0;
    this->error = false;
}

std::shared_ptr<Expr> Parser::parse(){
    return expression();
}

bool Parser::match(std::vector<TokenType> types){
    for(TokenType type : types){
        if(check(type)){
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(TokenType type){
    if(is_at_end()) return false;
    return peek().type == type;
}

Token Parser::advance(){
    if(!is_at_end()) current++;
    return previous();
}

bool Parser::is_at_end(){
    return peek().type == END;
}

Token Parser::peek(){
    return tokens.at(current);
}

Token Parser::previous(){
    return tokens.at(current - 1);
}

void Parser::consume(TokenType ttype, std::string msg){
    if(check(ttype)) {
        advance();
        return;
    }
    error = true;
    printf("ERROR: %s\n", msg.c_str());
}

std::shared_ptr<Expr> Parser::expression(){
    return term();
}

std::shared_ptr<Expr> Parser::term(){
    std::shared_ptr<Expr> expr = factor();

    while(match({MINUS, PLUS})){
        Token op = previous();
        std::shared_ptr<Expr> right = factor();
        expr = std::make_shared<Binary>(expr, std::move(op), right);
    }

    return expr;
}

std::shared_ptr<Expr> Parser::factor(){
    std::shared_ptr<Expr> expr = unary();

    while(match({STAR, SLASH})){
        Token op = previous();
        std::shared_ptr<Expr> right = unary();
        expr = std::make_shared<Binary>(expr, std::move(op), right);
    }

    return expr;
}
std::shared_ptr<Expr> Parser::unary(){
    // IMPLEMENT MINUS UNARY OP
    return primary();
}

std::shared_ptr<Expr> Parser::primary(){
    if(match({NUMBER})){
        return std::make_shared<Literal>(previous().value);
    }

    if(match({L_PAREN})){
        std::shared_ptr<Expr> expr = expression();
        consume(R_PAREN, "Expected ')' after expression");
        return std::make_shared<Grouping>(expr);
    }

    printf("ERROR: Unreachable code\n");
    error = true;
    return std::shared_ptr<Expr>(nullptr);
}
