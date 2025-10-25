#ifndef CLASSIFIED_TOKENIZER_H
#define CLASSIFIED_TOKENIZER_H

#include "raw_tokenizer.h"

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_DELIMITER
} TokenType;

typedef struct
{
    char *value;
    TokenType type;
    size_t length;
} ClassifiedToken;

typedef struct
{
    ClassifiedToken *tokens;
    size_t size;
    size_t capacity;
} ClassifiedTokenList;

ClassifiedTokenList* classified_tokenize(RawTokenList *raw_token_list);
void free_classified_token_list(ClassifiedTokenList *list);
#endif