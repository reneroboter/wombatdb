#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "classified_tokenizer.h"
#include <ctype.h>

int is_delimiter(RawToken *current_raw_token);
int is_keyword(RawToken *current_raw_token);
int is_operator(RawToken *current_raw_token);
int is_identifier(RawToken *current_raw_token);

ClassifiedToken *create_new_classified_token();
void push_classified_token_to_list(ClassifiedTokenList *list, ClassifiedToken token);

ClassifiedTokenList classified_tokenize(RawTokenList *raw_token_list)
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
            strcpy(classified_token->type, "KEYWORD");
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
            strcpy(classified_token->type, "OPERATOR");
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
            strcpy(classified_token->type, "DELIMITER");
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

            strcpy(classified_token->type, "IDENTIFIER");
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
    return *classified_token_list;
}

void push_classified_token_to_list(ClassifiedTokenList *list, ClassifiedToken token) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->tokens = realloc(list->tokens, list->capacity * sizeof(ClassifiedToken));

        if (list->tokens == NULL) {
            perror("Failed to reallocate memory for classified tokens list!");
            exit(-1);
        }
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
    char copy[current_raw_token->length];
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

int main() {
    RawTokenList *raw_token_list = malloc(sizeof(RawTokenList));
    raw_token_list->size = 1;
    raw_token_list->capacity = 11;
    raw_token_list->tokens = malloc(raw_token_list->capacity * sizeof(RawToken));

    // "SELECT name, age FROM wombats WHERE age > 3;",
    const char *token[] = {
        "SELECT",
        "name",
        ",",
        "age",
        "FROM",
        "wombats",
        "WHERE",
        "age",
        ">",
        "3",
        ";"
    };

    int token_size = sizeof(token) / sizeof(token[0]);

    for (int i = 0; i < token_size; i++) {
        printf("%s\n", token[i]);
        RawToken raw_token;
        raw_token.value = strcpy(raw_token.value, token[i]);
        raw_token.length = strlen(raw_token.value);
        raw_token_list->tokens[raw_token_list->size++] = raw_token;
    }

    ClassifiedTokenList result = classified_tokenize(raw_token_list);
    return 0;
}