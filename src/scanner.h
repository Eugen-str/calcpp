#ifndef SCANNER_H_
#define SCANNER_H_

#include <cstdint>
#include <string>
#include <vector>
#include "token.h"

class Scanner{
public:
    Scanner(std::string input);
    std::vector<Token> scan();
    bool error;
private:
    std::vector<Token> tokens;
    std::string input;
    uint32_t current;

    void scan_token();
    bool is_at_end();
    void add_token(TokenType ttype, double value);
    void add_token(TokenType ttype);
    char get_and_advance();
    char peek();
    char peek_next();
    void advance();
    void number();
};

#endif
