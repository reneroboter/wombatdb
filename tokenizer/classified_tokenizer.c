#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "classified_tokenizer.h"


int is_delimiter(RawToken *current_raw_token);
int is_keyword(RawToken *current_raw_token);
int is_operator(RawToken *current_raw_token);
int is_identifier(RawToken *current_raw_token);

ClassifiedToken *create_new_classified_token();
void push_classified_token_to_list(ClassifiedTokenList *list, ClassifiedToken token);

ClassifiedTokenList* classified_tokenize(RawTokenList *raw_token_list)
{
    ClassifiedTokenList *classified_token_list = malloc(sizeof(ClassifiedTokenList));

    if (classified_token_list == NULL) {
        perror("Failed to allocate memory for classified token list!");
        exit(-1);
    }

    classified_token_list->size = 0;
    classified_token_list->capacity = 4;
    classified_token_list->tokens = malloc(raw_token_list->size * sizeof(ClassifiedToken *));

    if (classified_token_list->tokens == NULL) {
        perror("Failed to allocate memory for classified tokens array!");
        exit(-1);
    }

    ClassifiedToken *classified_token = create_new_classified_token();

    int j = 0;
    while (j < raw_token_list->size - 1)
    {
        RawToken current_raw_token = raw_token_list->tokens[j];
        if (is_keyword(&current_raw_token))
        {
            classified_token->type = TOKEN_KEYWORD;
            strcpy(classified_token->value, current_raw_token.value);
            classified_token->length = current_raw_token.length;

            push_classified_token_to_list(classified_token_list, *classified_token);
            free(classified_token->value);
            free(classified_token);

            classified_token= create_new_classified_token();
            j++;
            continue;
        }

        if (is_operator(&current_raw_token))
        {
            classified_token->type = TOKEN_OPERATOR;
            strcpy(classified_token->value, current_raw_token.value);
            classified_token->length = current_raw_token.length;

            push_classified_token_to_list(classified_token_list, *classified_token);
            free(classified_token->value);
            free(classified_token);

            classified_token= create_new_classified_token();
            j++;
            continue;
        }

        if (is_delimiter(&current_raw_token))
        {
            classified_token->type = TOKEN_DELIMITER;
            strcpy(classified_token->value, current_raw_token.value);
            classified_token->length = current_raw_token.length;

            push_classified_token_to_list(classified_token_list, *classified_token);
            free(classified_token->value);
            free(classified_token);

            classified_token= create_new_classified_token();
            j++;
            continue;
        }

        // check manual if it's a string literal without regex!!
        if (is_identifier(&current_raw_token))
        {

            classified_token->type = TOKEN_IDENTIFIER;
            strcpy(classified_token->value, current_raw_token.value);
            classified_token->length = current_raw_token.length;

            push_classified_token_to_list(classified_token_list, *classified_token);
            free(classified_token->value);
            free(classified_token);

            classified_token= create_new_classified_token();
            j++;
            continue;
        }
        fprintf(stderr, "Could not classify current token! %s\n", current_raw_token.value);
        exit(-1);
    }
    return classified_token_list;
}

void free_classified_token_list(ClassifiedTokenList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->tokens[i].value);
    }

    free(list->tokens);

    list->tokens = NULL;
    list->size = 0;
    list->capacity = 0;
}

void push_classified_token_to_list(ClassifiedTokenList *list, ClassifiedToken token) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        ClassifiedToken *new_tokens = realloc(list->tokens, list->capacity * sizeof(ClassifiedToken));

        if (new_tokens == NULL) {
            perror("Failed to reallocate memory for classified tokens list!");
            exit(-1);
        }
        list->tokens = new_tokens;
    }

    ClassifiedToken copy_token = token;
    copy_token.length = token.length;
    copy_token.value = malloc(token.length + 1);

    strcpy(copy_token.value, token.value);

    list->tokens[list->size++] = token;
}

ClassifiedToken *create_new_classified_token() {
    ClassifiedToken *classified_token = malloc(sizeof(ClassifiedToken));

    if (classified_token == NULL) {
        perror("Failed to allocate memory for raw token!");
        exit(-1);
    }

    classified_token->length = 0;
    classified_token->value = malloc(classified_token->length + 1);

    if (classified_token->value == NULL) {
        perror("Failed to allocate memory for classified_token token value!");
        free(classified_token);
        exit(-1);
    }

    return classified_token;
}

int is_operator(RawToken *current_raw_token) {
    char copy[current_raw_token->length];
    strcpy(copy, current_raw_token->value);

    return strcmp(copy, ">") == 0 ||
           strcmp(copy, "<") == 0 ||
           strcmp(copy, "=") == 0;
}

int is_delimiter(RawToken *current_raw_token) {
    char copy[current_raw_token->length];
    strcpy(copy, current_raw_token->value);

    return strcmp(copy, "(") == 0 ||
           strcmp(copy, ")") == 0 ||
           strcmp(copy, ",") == 0 ||
           strcmp(copy, ";") == 0;
}

int is_keyword(RawToken *current_raw_token)
{
    char *copy = malloc(current_raw_token->length + 1);
    strcpy(copy, current_raw_token->value);

    for(int i = 0; copy[i]; i++){
        copy[i] = tolower(copy[i]);
    }

    return strcmp(copy, "select") == 0 ||
           strcmp(copy, "from") == 0 ||
           strcmp(copy, "where") == 0 ||
           strcmp(copy, "order") == 0 ||
           strcmp(copy, "by") == 0 ||
           strcmp(copy, "asc") == 0 ||
           strcmp(copy, "dsc") == 0 ||
           strcmp(copy, "limit") == 0 ||
           strcmp(copy, "offset") == 0 ||
           strcmp(copy, "insert") == 0 ||
           strcmp(copy, "into") == 0 ||
           strcmp(copy, "values") == 0 ||
           strcmp(copy, "create") == 0 ||
           strcmp(copy, "table") == 0;
}

int is_identifier(RawToken *current_raw_token) {
    return 0;
}