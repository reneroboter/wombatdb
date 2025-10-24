#ifndef RAW_TOKENIZER_H
#define RAW_TOKENIZER_H

typedef struct
{
    char *value;
    size_t length;
} RawToken;

typedef struct
{
    RawToken *tokens;
    size_t size;
    size_t capacity;
} RawTokenList;

RawTokenList raw_tokenize(const char query[]);

#endif