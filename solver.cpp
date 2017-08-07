
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
    TokenType_LeftParen,
    TokenType_RightParen,
};

// @TODO: vectors, 

enum NumberType {
    NumberType_Int,
    NumberType_Real,
    NumberType_Imaginary,
};

enum OperatorType {
    OperatorType_Add,
    OperatorType_Sub,
    OperatorType_Mult,
    OperatorType_Div,
};

// given tree tell if the tree is a complex expression

struct Tokenizer {
    char *buffer;
    uint32 index;

    char *at;
};

struct Token {
    TokenType type;

    uint32 length;
    char *str;
};

bool CharIsOperator(char c) {
    return c == '=' || c == '+' || c == '-' || c == '*' || c == '/';
}

bool CharIsDigit(char c) {
    return c >= 48 && c <= 57;
}

bool CharIsLeftParen(char c) {
    return c == '(';
}

bool CharIsRightParen(char c) {
    return c == ')';
}

bool ConsumeChar(Tokenizer *tokenizer, char c) {
    char character = tokenizer->buffer[tokenizer->index];

    if (c == character) {
        tokenizer->index++;
        return true;
    }

    return false;
}

bool ConsumeWhitespace(Tokenizer *tokenizer) {
    bool result = false;
    
    char c = tokenizer->buffer[tokenizer->index];

    while (c == ' ') {
        tokenizer->index++;
        c = tokenizer->buffer[tokenizer->index];

        result = true;
    }

    return result;
}

uint32 TrimRightWhitespace(char *str, uint32 length) {

    while(str[length - 1] == ' ') {
        length--;
    }

    str[length] = 0;
    Print("%s", str);

    return length;
}

uint32 TokenizeEquation(char *equationString, uint32 length, Token *tokens) {
    uint32 tokenCount = 0;

    length = TrimRightWhitespace(equationString, length);

    Tokenizer tokenizer = {};
    tokenizer.buffer = equationString;

    bool insideToken = false;
    Token currToken = {};
    while (*(tokenizer.buffer + tokenizer.index) != 0) {

        // tokens[tokenCount] = GetNextToken(&tokenizer);
        // tokenCount++;
        
        if (ConsumeWhitespace(&tokenizer)) {
            tokens[tokenCount] = currToken;

            tokenCount++;

            currToken = {};
            insideToken = false;
        }

        if (ConsumeChar(&tokenizer, '(')) {
            tokens[tokenCount] = currToken;
            tokenCount++;

            currToken.type = TokenType_LeftParen;
            currToken.str = tokenizer.buffer + (tokenizer.index - 1);
            currToken.length = 1;

            tokens[tokenCount] = currToken;
            tokenCount++;

            currToken = {};
            insideToken = false;
        }
        else if (ConsumeChar(&tokenizer, ')')) {
            tokens[tokenCount] = currToken;
            tokenCount++;

            currToken.type = TokenType_RightParen;
            currToken.str = tokenizer.buffer + (tokenizer.index - 1);
            currToken.length = 1;

            tokens[tokenCount] = currToken;
            tokenCount++;

            currToken = {};
            insideToken = false;
        }

        ConsumeWhitespace(&tokenizer);

        if (!insideToken) {
            currToken.str = tokenizer.buffer + tokenizer.index;

            if (CharIsOperator(currToken.str[0])) {
                currToken.type = TokenType_Operator;
            }
            if (CharIsDigit(currToken.str[0])) {
                currToken.type = TokenType_Number;
            }
            else {
                currToken.type = TokenType_Variable;
            }

            currToken.length = 1;

            insideToken = true;
        }
        else {
            char c = *(tokenizer.buffer + tokenizer.index);
            if (currToken.type == TokenType_Number) {
                if (!CharIsDigit(c)) {
                    tokens[tokenCount] = currToken;
                    tokenCount++;

                    currToken = {};
                    insideToken = false;

                    // @GACK: what I dont like about this is that we have finished a token
                    // (should probably be it's own function), but the current character
                    // hasnt been dealt with yet, so we dont want to increment the index
                    // and dont want a flag saying if we should or not...
                    // write as ConsumeFunctions
                    continue;
                }
                else {
                    currToken.length++;
                }
            }
            else {
                currToken.length++;
            }
        }

        tokenizer.index++;
    }

    tokens[tokenCount] = currToken;
    tokenCount++;

    return tokenCount;
}

int main() {
    const char *equationStr = "force = mass * acceleration";
    //const char *equationStr = "f(x) = 7x / 4";

    char *equationStrCpy = (char *)malloc(strlen(equationStr));
    memcpy(equationStrCpy, equationStr, strlen(equationStr));

    Token *tokens = (Token *)malloc(sizeof(Token) * 1024);

#if 1
    uint32 tokenCount = TokenizeEquation(equationStrCpy, strlen(equationStrCpy), tokens);

    Print("tokenCount %d", tokenCount);

    for (int i = 0; i < tokenCount; i++) {
        Print("%.*s tokenType %d", tokens[i].length, tokens[i].str, tokens[i].type);
    }
#endif    
    return 0;
}
