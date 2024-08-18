#ifndef TOKEN_H_
#define TOKEN_H_

typedef enum {
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    L_PAREN,
    R_PAREN,
    END
}TokenType;

class Token {
public:
    TokenType type;
    double value;

    Token(TokenType ttype, double value);
};

#endif
