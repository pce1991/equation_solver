
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdarg.h>

#include "solver_types.h"

struct String {
    uint32 length;
};

// take input equation
// derive
// output equation

// x + y/b * Y/z + 100.0234

void Print(const char *fmt, ...) {
    const uint32 maxBufferLength = 2048;
    char buffer[maxBufferLength];

    va_list args;
    va_start(args, fmt);

    vsnprintf(buffer, maxBufferLength, fmt, args);

    printf("%s\n", buffer);

    va_end(args);
}

char *QuotientRule(char *quotient) {
    char *deriv = NULL;

    // does some stuff

    return deriv;
}

enum TokenType {
    TokenType_Number,
    TokenType_Variable,
    TokenType_Operator,
    TokenType_Function,
    TokenType_Derivative,
};

struct Token {
    TokenType type;

    uint32 length;
    char *str;
};



int main() {
    const char *equationStr = "F = m * a";

    Token t;
    t.type = TokenType_Variable;

    return 0;
}
