#ifndef RAW_TOKENIZER_H
#define RAW_TOKENIZER_H

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

RawTokenList tokenizer(const char query[], size_t query_length);

#endif