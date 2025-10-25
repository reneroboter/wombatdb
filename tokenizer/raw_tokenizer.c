#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raw_tokenizer.h"

int is_space(char c);
int is_raw_operator(char c);

RawTokenList* raw_tokenize(const char query[]) {
    // calloc
    RawTokenList *raw_token_list = malloc(sizeof(RawTokenList));

    if (raw_token_list == NULL) {
        perror("Failed to allocate memory for raw token list!");
        exit(-1);
    }

    raw_token_list->size = 0;
    raw_token_list->capacity = 4;
    raw_token_list->tokens = malloc(raw_token_list->capacity * sizeof(RawToken));

    if (raw_token_list->tokens == NULL) {
        perror("Failed to allocate memory for tokens array!");
        exit(-1);
    }

    RawToken *raw_token = create_new_raw_token();

    int i = 0;

    while (query[i] != '\0') {
        const char current_char = query[i];

        if (is_space(current_char)) {
            if (raw_token->length > 0) {
                raw_token->value[raw_token->length] = '\0';
                push_raw_token_to_list(raw_token_list, *raw_token);
                free(raw_token->value);
                free(raw_token);
                raw_token = create_new_raw_token();
            }
            i++;
            continue;
        }

        if (is_raw_operator(current_char)) {
            // previous token e.g "name,"
            // store "name"
            if (raw_token->length > 0) {
                raw_token->value[raw_token->length] = '\0';
                push_raw_token_to_list(raw_token_list, *raw_token);
                free(raw_token->value);
                free(raw_token);
            }

            // store ","
            raw_token = create_new_raw_token();
            raw_token->value[raw_token->length++] = current_char;
            raw_token->value[raw_token->length] = '\0';
            push_raw_token_to_list(raw_token_list, *raw_token);
            free(raw_token->value);
            free(raw_token);

            // create new token
            raw_token = create_new_raw_token();

            i++;
            continue;
        }

        push_char_to_current_token(raw_token, current_char);

        i++;
    }

    // check if token still exists
    if (raw_token->length > 0) {
        raw_token->value[raw_token->length] = '\0';
        push_raw_token_to_list(raw_token_list, *raw_token);
        free(raw_token->value);
        free(raw_token);
    }

    return raw_token_list;
}
void push_char_to_current_token(RawToken *token, const char c) {
    if (token->length >= token->capacity) {
        token->capacity *= 2;
        char *new_value = realloc(token->value, token->capacity * sizeof(char));

        if (new_value == NULL) {
            perror("Failed to reallocate memory for raw token value!");
            exit(-1);
        }
        token->value = new_value;

    }
    token->value[token->length++] = c;
}
void free_raw_token_list(RawTokenList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->tokens[i].value);
    }

    free(list->tokens);

    list->tokens = NULL;
    list->size = 0;
    list->capacity = 0;
}

void push_raw_token_to_list(RawTokenList *list, const RawToken token) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        RawToken *new_tokens = realloc(list->tokens, list->capacity * sizeof(RawToken));

        if (new_tokens == NULL) {
            perror("Failed to reallocate memory for raw tokens list!");
            exit(-1);
        }
        list->tokens = new_tokens;
    }

    // I already have a copy, bc by value, but the token value is a pointer!
    RawToken copy_token;
    copy_token.length = token.length;
    copy_token.capacity = token.capacity;
    copy_token.value = malloc(token.length + 1);

    if (copy_token.value == NULL) {
        perror("Failed to allocate memory for copy token!");
        exit(-1);
    }

    memcpy(copy_token.value, token.value, token.length + 1);

    list->tokens[list->size++] = copy_token;
}

RawToken *create_new_raw_token() {
    RawToken *raw_token = malloc(sizeof(RawToken));

    if (raw_token == NULL) {
        perror("Failed to allocate memory for raw token!");
        exit(-1);
    }

    raw_token->length = 0;
    raw_token->capacity = 4;
    raw_token->value = malloc(raw_token->capacity);

    if (raw_token->value == NULL) {
        perror("Failed to allocate memory for raw token value!");
        free(raw_token);
        exit(-1);
    }

    return raw_token;
}

int is_space(const char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

int is_raw_operator(const char c) {
    return c == '>' || c == '<' || c == '=' || c == '(' || c == ')' || c == ',' || c == ';';
}
