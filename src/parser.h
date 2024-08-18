#ifndef PARSER_H_
#define PARSER_H_

#include "expr.h"
#include "token.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

class Parser {
public:
    Parser(std::vector<Token> tokens);
    std::shared_ptr<Expr> parse();

    bool error;
private:
    std::vector<Token> tokens;
    uint32_t current;

    bool match(std::vector<TokenType> types);
    bool check(TokenType type);
    Token advance();
    bool is_at_end();
    Token peek();
    Token previous();
    void consume(TokenType ttype, std::string msg);

    std::shared_ptr<Expr> expression();
    std::shared_ptr<Expr> term();
    std::shared_ptr<Expr> factor();
    std::shared_ptr<Expr> unary();
    std::shared_ptr<Expr> primary();
};

#endif
