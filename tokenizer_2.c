#include <stdio.h>
#include <string.h>
#include "tokenizer_2.h"

int is_space(char c);
int is_raw_operator(char *c);
int is_delimiter(RawToken *current_raw_token);
int is_keyword(RawToken *current_raw_token);
int is_operator(RawToken *current_raw_token);
int is_identifier(RawToken *current_raw_token);

ClassifiedTokenList tokenizer(const char query[], size_t query_length)
{
    // todo how to do dynamically allocate memory?!
    RawTokenList raw_token_list;
    raw_token_list.size = 0;

    RawToken raw_token;
    raw_token.length = 0;

    int i = 0;

    // identify raw tokens
    while (query[i] != '\0')
    {
        char current_char = query[i];


        // todo how to do dynamically allocate memory?!
        if (is_space(current_char))
        {
            raw_token.value[raw_token.length] = '\0';
            raw_token_list.tokens[raw_token_list.size++] = raw_token;

            raw_token = (RawToken){.value = "", .length = 0};

            i++;
            continue;
        }

        if (is_raw_operator(&current_char))
        {
            // previous token e.g "name,"
            // store "name"
            raw_token.value[raw_token.length] = '\0';
            raw_token_list.tokens[raw_token_list.size++] = raw_token;

            // store ","
            raw_token = (RawToken){.value = "", .length = 0};
            raw_token.value[raw_token.length++] = current_char;
            raw_token.value[raw_token.length] = '\0';
            raw_token_list.tokens[raw_token_list.size++] = raw_token;

            i++;
            continue;
        }

        raw_token.value[raw_token.length++] = current_char;

        i++;
    }

    // todo how to do dynamically allocate memory?!
    ClassifiedTokenList classified_token_list;
    classified_token_list.size = 0;

    ClassifiedToken classified_token;
    classified_token.length = 0;

    // identify raw tokens
    int j;
    while (j < raw_token_list.size - 1)
    {
        RawToken current_raw_token = raw_token_list.tokens[j];
        if (is_keyword(&current_raw_token))
        {
            strcpy(classified_token.type, "KEYWORD");
            strcpy(classified_token.value, current_raw_token.value);
            classified_token.length = current_raw_token.length;

            classified_token_list.tokens[classified_token_list.size++] = classified_token;

            classified_token = (ClassifiedToken){.value = "", .length = 0};
            i++;
            continue;
        }

        if (is_operator(&current_raw_token))
        {
            strcpy(classified_token.type, "OPERATOR");
            strcpy(classified_token.value, current_raw_token.value);
            classified_token.length = current_raw_token.length;

            classified_token_list.tokens[classified_token_list.size++] = classified_token;

            classified_token = (ClassifiedToken){.value = "", .length = 0};
            i++;
            continue;
        }

        if (is_delimiter(&current_raw_token))
        {
            strcpy(classified_token.type, "DELIMITER");
            strcpy(classified_token.value, current_raw_token.value);
            classified_token.length = current_raw_token.length;

            classified_token_list.tokens[classified_token_list.size++] = classified_token;

            classified_token = (ClassifiedToken){.value = "", .length = 0};
            i++;
            continue;
        }

        // check manual if its a string literal without regex!!
        if (is_identifier(&current_raw_token))
        {

            strcpy(classified_token.type, "DELIMITER");
            strcpy(classified_token.value, current_raw_token.value);
            classified_token.length = current_raw_token.length;

            classified_token_list.tokens[classified_token_list.size++] = classified_token;

            classified_token = (ClassifiedToken){.value = "", .length = 0};
            i++;
            continue;
        }

        // todo is identifier -> how to?
        // todo throw error CANT CLASSIFIED TOKEN
    }
    return classified_token_list;
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
        ClassifiedTokenList result = tokenizer(query, strlen(query) + 1);
        for (int j = 0; j < result.size; j++)
        {
            printf("TYPE: %d: %s\n", j, result.tokens[j].type);
            printf("VALUE: %d: %s\n", j, result.tokens[j].value);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
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