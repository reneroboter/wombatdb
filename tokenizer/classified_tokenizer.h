#ifndef CLASSIFIED_TOKENIZER_H
#define CLASSIFIED_TOKENIZER_H

#include "raw_tokenizer.h"

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
    size_t capacity;
} ClassifiedTokenList;

ClassifiedTokenList classified_tokenize(RawTokenList *raw_token_list);

#endif