#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../tokenizer/classified_tokenizer.h"

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_KEYWORD:    return "KEYWORD";
        case TOKEN_DELIMITER:  return "DELIMITER";
        case TOKEN_OPERATOR:   return "OPERATOR";
        default:               return "UNKNOWN";
    }
}

int main() {
    RawTokenList *raw_token_list = malloc(sizeof(RawTokenList));
    raw_token_list->size = 0;
    raw_token_list->capacity = 4;
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
        RawToken *raw_token = create_new_raw_token();
        strcpy(raw_token->value, token[i]);
        raw_token->length = strlen(token[i]);
        push_raw_token_to_list(raw_token_list, *raw_token);
        // printf("%s\n", token[i]);
    }


    ClassifiedTokenList* result = classified_tokenize(raw_token_list);
    for (int j = 0; j < result->size; j++) {


        printf("VALUE %d -> %s || ", j, result->tokens[j].value);
        printf("TYPE %d -> %s || ", j, token_type_to_string(result->tokens[j].type));
        printf("\n");
    }
    printf("\n");
    free_raw_token_list(raw_token_list);
    free_classified_token_list(result);
    return 0;
}