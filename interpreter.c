#include <stdio.h>
#include <string.h>
#include "tokenizer.h"

 enum tokenType {
    KEYWORD,
    IDENTIFIER,
    COMMA,
    OPERATOR,
    SEMICOLON
};

int main(void) {
    char *data_provider[] = {
        "SELECT name, age FROM wombats WHERE age > 3;",
        "SELECT name,age FROM wombats WHERE age > 4;",
        "SELECT  name,age  FROM wombats WHERE age > 5;",
        "SELECT name, age FROM     wombats WHERE age>6;",
        "SELECT     name, age FROM     wombats WHERE age     >7;"
    };

    int data_provider_count = sizeof(data_provider) / sizeof(data_provider[0]);

    for (int i = 0; i < data_provider_count; i++) {
        char query[256];
        strcpy(query, data_provider[i]);
        
        printf("TOKEN: %d\n", i);
        struct TokenList result = tokenizer(query, strlen(query) + 1);
        for (int j = 0; j < result.count; j++) {
            printf("TYPE: %d: %s\n", j, result.tokens[j].type);
            printf("VALUE: %d: %s\n", j, result.tokens[j].value);
            printf("\n");
        }
        printf("\n");

    } 

    return 0;
}
