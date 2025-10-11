#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

struct Token {
    char value[64];
    char type[20];
    int length;
};

struct TokenList {
    struct Token tokens[100];
    int count;
};

struct TokenList tokenizer(const char query[], size_t queryLength);

#endif