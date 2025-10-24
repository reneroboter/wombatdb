#ifndef CLASSIFIED_TOKENIZER_H
#define CLASSIFIED_TOKENIZER_H

#include <stddef.h>

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

ClassifiedTokenList tokenizer(RawTokenList *raw_token_list);

#endif