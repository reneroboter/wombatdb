#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "classified_tokenizer.h"

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