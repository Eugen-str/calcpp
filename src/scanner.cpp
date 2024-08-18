#include "scanner.h"
#include "token.h"
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>

Token::Token(TokenType ttype, double value){
    type = ttype;
    this->value = value;
}

Scanner::Scanner(std::string input){
    this->input = input;
    this->current = 0;
    this->tokens = std::vector<Token>();
    this->error = false;
}

void Scanner::add_token(TokenType ttype, double value){
    tokens.push_back(Token(ttype, value));
}

void Scanner::add_token(TokenType ttype){
    tokens.push_back(Token(ttype, -1));
}

char Scanner::peek(){
    if(is_at_end()) return '\0';
    return input.at(current);
}

char Scanner::peek_next(){
    if(current + 1 >= input.length()) return '\0';
    return input.at(current + 1);
}

void Scanner::advance(){
    current++;
}

char Scanner::get_and_advance(){
    char current_char = input.at(current);
    current++;
    return current_char;
}
void Scanner::number(){
    int start = current - 1;

    while(isdigit(peek())){
        advance();
    }

    if(peek() == '.'){
        if(!isdigit(peek_next())){
            printf("ERROR: expected fractional part of number after '.' on index %d\n", current);
            error = true;
        }
        advance();
        while(isdigit(peek())){
            advance();
        }
    }

    std::string result = input.substr(start, current);
    add_token(NUMBER, std::stod(result));
}

void Scanner::scan_token(){
    char c = get_and_advance();
    switch(c){
        case ' ':
            break;
        case '+':
            add_token(PLUS);
            break;
        case '-':
            add_token(MINUS);
            break;
        case '*':
            add_token(STAR);
            break;
        case '/':
            add_token(SLASH);
            break;
        case '(':
            add_token(L_PAREN);
            break;
        case ')':
            add_token(R_PAREN);
            break;
        default:
            if(isdigit(c)){
                number();
            } else {
                printf("ERROR: unknown character at index %d\n", current);
                error = true;
            }
            break;
    }
}

bool Scanner::is_at_end(){
    if(current >= input.length()) return true;
    return false;
}

std::vector<Token> Scanner::scan(){
    while(!is_at_end() && error == false){
        scan_token();
    }

    add_token(END);
    return tokens;
}
