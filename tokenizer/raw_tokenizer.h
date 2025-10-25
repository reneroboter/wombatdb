#ifndef RAW_TOKENIZER_H
#define RAW_TOKENIZER_H

typedef struct
{
    char *value;
    size_t length;
    size_t capacity;
} RawToken;

typedef struct
{
    RawToken *tokens;
    size_t size;
    size_t capacity;
} RawTokenList;

RawTokenList* raw_tokenize(const char query[]);
RawToken *create_new_raw_token();
void free_raw_token_list(RawTokenList *list);
void push_raw_token_to_list(RawTokenList *list, RawToken token);
void push_char_to_current_token(RawToken *token, char c);
#endif