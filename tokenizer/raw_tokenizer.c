#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raw_tokenizer.h"

int is_space(char c);
int is_raw_operator(char *c);

RawTokenList tokenizer(const char query[], size_t query_length)
{
    // todo how to do dynamically allocate memory?!
    RawTokenList raw_token_list;
    raw_token_list.size = 0;

    RawToken *raw_token = malloc(sizeof(RawToken));

    if (raw_token == NULL)
    {
        perror("Failed to allocate memory for raw token!");
        exit(-1);
    }

    raw_token->length = 0;
    raw_token->value = malloc(raw_token->length + 1);

    if (raw_token->value == NULL)
    {
        perror("Failed to allocate memory for raw token value!");
        free(raw_token);
        exit(-1);
    }

    int i = 0;

    // identify raw tokens
    while (query[i] != '\0')
    {
        char current_char = query[i];

        // todo how to do dynamically allocate memory?!
        // when should I free the memory?
        if (is_space(current_char))
        {
            raw_token->value[raw_token->length] = '\0';
            raw_token_list.tokens[raw_token_list.size++] = *raw_token;

            // ALLOCATE MEMORY HERE
            raw_token = (RawToken){.value = "", .length = 0};

            i++;
            continue;
        }

        if (is_raw_operator(&current_char))
        {
            // previous token e.g "name,"
            // store "name"
            raw_token->value[raw_token->length] = '\0';
            raw_token_list.tokens[raw_token_list.size++] = *raw_token;

            // store ","
            raw_token = (RawToken){.value = "", .length = 0};
            raw_token->value[raw_token->length++] = current_char;
            raw_token->value[raw_token->length] = '\0';
            raw_token_list.tokens[raw_token_list.size++] = *raw_token;

            i++;
            continue;
        }

        raw_token->value[raw_token->length++] = current_char;

        i++;
    }

    return raw_token_list;
}

RawToken create_new_raw_token() {
    
}

int is_space(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r';
}

int is_raw_operator(char *c)
{
    char first_c = *c; // same as c[0]
    return first_c == '>' || first_c == '<' || first_c == '=' || first_c == '(' || first_c == ')' || first_c == ',' || first_c == ';';
}

int main()
{
    char *data_provider[] = {
        "SELECT name, age FROM wombats WHERE age > 3;",
        "SELECT name,age FROM wombats WHERE age > 4;",
        "SELECT  name,age  FROM wombats WHERE age > 5;",
        "SELECT name, age FROM     wombats WHERE age>6;",
        "SELECT     name, age FROM     wombats WHERE age     >7;",
        "SELECT name, age FROM wombats WHERE age > 7 ORDER BY age ASC;",
        "SELECT name, age FROM wombats WHERE age > 7 ORDER BY age ASC LIMIT 1 OFFSET 2;",
        "INSERT INTO table_name (column1, column2, column3) VALUES (value1, value2, value3);",
        "CREATE TABLE table_name (column1, column2, column3);"};

    int data_provider_count = sizeof(data_provider) / sizeof(data_provider[0]);

    for (int i = 0; i < data_provider_count; i++)
    {
        char query[256];
        strcpy(query, data_provider[i]);

        printf("TOKEN: %d\n", i);
        RawTokenList result = tokenizer(query, strlen(query) + 1);
        for (int j = 0; j < result.size; j++)
        {
            printf("VALUE: %d: %s\n", j, result.tokens[j].value);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}