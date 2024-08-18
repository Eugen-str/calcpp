#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

#include "scanner.h"
#include "token.h"
#include "parser.h"
#include "interpreter.h"

using namespace std;

void print_result(double x){
    if(trunc(x) == x){
        printf("%.0f\n", x);
    }
    else{
        printf("%.3f\n", x);
    }
}

void calculate(string input){
    Scanner scanner = Scanner(input);
    vector<Token> tokens = scanner.scan();

    if(scanner.error) return;

    Parser parser = Parser(tokens);
    shared_ptr<Expr> expression = parser.parse();

    if(parser.error) return;

    Interpreter interpreter;

    if(interpreter.error) return;

    double result = interpreter.interpret(expression);

    print_result(result);
}

int main(int argc, char** argv){
    if(argc == 1){
        string input;

        printf("; ");
        while(getline(cin, input)){
            if(input == "quit") {
                break;
            }
            calculate(input);
            printf("; ");
        }
    } else if (argc == 2){
        calculate(argv[1]);
    } else {
        printf("ERROR: Unknown parameters\n");
        return 1;
    }

    return 0;
}
