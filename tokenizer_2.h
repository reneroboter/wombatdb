#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

typedef struct
{
    char *value;
    size_t length;
} RawToken;

typedef struct
{
    RawToken *tokens;
    size_t size;
} RawTokenList;

typedef struct
{
    char *value;
    char *type; // todo use enum 
    size_t length;
} ClassifiedToken;

typedef struct
{
    ClassifiedToken *tokens;
    size_t size;
} ClassifiedTokenList;

ClassifiedTokenList tokenizer(const char query[], size_t query_length);

#endif