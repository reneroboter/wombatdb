#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tokenizer/classified_tokenizer.h"


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
        raw_token.capacity = 4;
        raw_token_list->tokens[raw_token_list->size++] = raw_token;
    }


    ClassifiedTokenList* result = classified_tokenize(raw_token_list);
    for (int j = 0; j < result->size; j++) {
        printf("TYPE %d -> %s || ", j, result->tokens[j].value);
        printf("\n");
        printf("VALUE %d -> %s || ", j, result->tokens[j].value);
    }
    printf("\n");
    free_raw_token_list(raw_token_list);
    free_classified_token_list(result);
    return 0;
}