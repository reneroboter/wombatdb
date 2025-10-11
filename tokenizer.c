#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tokenizer.h"
#include <stdbool.h>

bool is_keyword(const char query[])
{
    // todo
    // str to lower
    // check again then
    return strcmp(query, "SELECT") == 0 ||
           strcmp(query, "FROM") == 0 ||
           strcmp(query, "WHERE") == 0 ||
           strcmp(query, "ORDER") == 0 ||
           strcmp(query, "BY") == 0 ||
           strcmp(query, "ASC") == 0 ||
           strcmp(query, "DSC") == 0 ||
           strcmp(query, "LIMIT") == 0 ||
           strcmp(query, "OFFSET") == 0 ||
           strcmp(query, "INSERT") == 0 ||
           strcmp(query, "INTO") == 0 ||
           strcmp(query, "VALUES") == 0 ||
           strcmp(query, "CREATE") == 0 ||
           strcmp(query, "TABLE") == 0;
}

bool is_operator(char c)
{
    // printf("IS_OPERATOR: %c\n", c);
    return c == '>' || c == '<' || c == '=' || c == '(' || c == ')' || c == ',' || c == ';';
}

struct TokenList tokenizer(const char query[], size_t queryLength)
{
    int i = 0;
    struct TokenList tokenList;
    tokenList.count = 0;

    struct Token token = {.value = "", .length = 0};

    char temp[256];
    strcpy(temp, query);

    while (i < queryLength - 1) // todo check on termination char
    {

        char c = temp[i];

        // SELECT name,age  FROM
        if (isspace(c) && token.length < 1)
        {
            i++;
            continue;
        }

        if (isspace(c) && token.length > 0)
        {
            if (is_keyword(token.value))
            {
                strcpy(token.type, "KEYWORD");
                token.value[token.length] = '\0';
                tokenList.tokens[tokenList.count++] = token;

                token = (struct Token){.value = "", .length = 0};
                i++;
                continue;
            }

            if (is_operator(c))
            {
                // previous identifier
                strcpy(token.type, "IDENTIFIER");
                token.value[token.length] = '\0';
                tokenList.tokens[tokenList.count++] = token;

                // operator
                token = (struct Token){.value = "", .length = 0};
                strcpy(token.type, "OPERATOR");
                token.value[token.length++] = c;
                token.value[token.length] = '\0';
                tokenList.tokens[tokenList.count++] = token;

                // new token
                token = (struct Token){.value = "", .length = 0};
                i++;
                continue;
            }

            strcpy(token.type, "IDENTIFIER");
            token.value[token.length] = '\0';
            tokenList.tokens[tokenList.count++] = token;

            token = (struct Token){.value = "", .length = 0};
            i++;
            continue;
        }

        if (is_keyword(token.value))
        {
            strcpy(token.type, "KEYWORD");
            token.value[token.length] = '\0';
            tokenList.tokens[tokenList.count++] = token;

            token = (struct Token){.value = "", .length = 0};
        }

        if (is_operator(c))
        {
            // previous identifier

            if (token.length > 0)
            {
                strcpy(token.type, "IDENTIFIER");
                token.value[token.length] = '\0';
                tokenList.tokens[tokenList.count++] = token;
            }

            // operator
            token = (struct Token){.value = "", .length = 0};
            strcpy(token.type, "OPERATOR");
            token.value[token.length++] = c;
            token.value[token.length] = '\0';
            tokenList.tokens[tokenList.count++] = token;

            // new token
            token = (struct Token){.value = "", .length = 0};
            i++;
            continue;
        }

        token.value[token.length++] = c;

        i++;
    };
    return tokenList;
}