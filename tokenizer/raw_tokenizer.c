#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raw_tokenizer.h"

int is_space(char c);

int is_raw_operator(char c);

RawToken *create_new_raw_token();

void push_raw_token_to_list(RawTokenList *list, RawToken token);

RawTokenList tokenizer(const char query[], size_t query_length) {
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
        char current_char = query[i];

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
            raw_token->value = realloc(raw_token->value, raw_token->length + 2);
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

        raw_token->value = realloc(raw_token->value, raw_token->length + 2);
        raw_token->value[raw_token->length++] = current_char;

        i++;
    }

    return *raw_token_list;
}

void push_raw_token_to_list(RawTokenList *list, RawToken token) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->tokens = realloc(list->tokens, list->capacity * sizeof(RawToken));

        if (list->tokens == NULL) {
            perror("Failed to reallocate memory for raw tokens list!");
            exit(-1);
        }
    }

    RawToken copy_token = token;
    copy_token.length = token.length;
    copy_token.value = malloc(token.length + 1);

    strcpy(copy_token.value, token.value);

    list->tokens[list->size++] = copy_token;
}

RawToken *create_new_raw_token() {
    RawToken *raw_token = malloc(sizeof(RawToken));

    if (raw_token == NULL) {
        perror("Failed to allocate memory for raw token!");
        exit(-1);
    }

    raw_token->length = 0;
    raw_token->value = malloc(raw_token->length + 1);

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

int main() {
    char *data_provider[] = {
        "SELECT name, age FROM wombats WHERE age > 3;",
        "SELECT name,age FROM wombats WHERE age > 4;",
        "SELECT  name,age  FROM wombats WHERE age > 5;",
        "SELECT name, age FROM     wombats WHERE age>6;",
        "SELECT     name, age FROM     wombats WHERE age     >7;",
        "SELECT name, age FROM wombats WHERE age > 7 ORDER BY age ASC;",
        "SELECT name, age FROM wombats WHERE age > 7 ORDER BY age ASC LIMIT 1 OFFSET 2;",
        "INSERT INTO table_name (column1, column2, column3) VALUES (value1, value2, value3);",
        "CREATE TABLE table_name (column1, column2, column3);"
    };

    int data_provider_count = sizeof(data_provider) / sizeof(data_provider[0]);

    for (int i = 0; i < data_provider_count; i++) {
        char query[256];
        strcpy(query, data_provider[i]);

        //printf("RAW TOKEN: %d\n", i);
        RawTokenList result = tokenizer(query, strlen(query) + 1);
        for (int j = 0; j < result.size; j++) {
            printf("VALUE %d -> %s || ", j, result.tokens[j].value);
        }
        printf("\n");
    }
    return 0;
}
