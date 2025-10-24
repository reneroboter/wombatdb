#include <stdio.h>
#include <string.h>
#include "classified_tokenizer.h"

int is_delimiter(RawToken *current_raw_token);
int is_keyword(RawToken *current_raw_token);
int is_operator(RawToken *current_raw_token);
int is_identifier(RawToken *current_raw_token);

ClassifiedTokenList tokenizer(RawTokenList *raw_token_list);
{
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