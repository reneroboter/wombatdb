#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "tokenizer.h"
#include <string.h>

void test_tokenizer_1(void) {

    char *data_provider[] = {
        "SELECT name, age FROM wombats WHERE age > 3;",
        "SELECT name,age FROM wombats WHERE age > 3;",
        "SELECT  name,age  FROM wombats WHERE age > 3;",
        "SELECT name, age FROM     wombats WHERE age>3;",
        "SELECT     name, age FROM     wombats WHERE age     >3;"
    };

    int data_provider_count = sizeof(data_provider) / sizeof(data_provider[0]);

    for (int i = 0; i < data_provider_count; i++) {
        char query[256];
        strcpy(query, data_provider[i]);
        
        struct TokenList result = tokenizer(query, strlen(query) + 1);

        CU_ASSERT_EQUAL(result.count, 11);

        CU_ASSERT_STRING_EQUAL(result.tokens[0].value, "SELECT");
        CU_ASSERT_STRING_EQUAL(result.tokens[1].value, "name");
        CU_ASSERT_STRING_EQUAL(result.tokens[2].value, ",");
        CU_ASSERT_STRING_EQUAL(result.tokens[3].value, "age");
        CU_ASSERT_STRING_EQUAL(result.tokens[4].value, "FROM");
        CU_ASSERT_STRING_EQUAL(result.tokens[5].value, "wombats");
        CU_ASSERT_STRING_EQUAL(result.tokens[6].value, "WHERE");
        CU_ASSERT_STRING_EQUAL(result.tokens[7].value, "age");
        CU_ASSERT_STRING_EQUAL(result.tokens[8].value, ">");
        CU_ASSERT_STRING_EQUAL(result.tokens[9].value, "3");
    }
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("AddTestSuite", 0, 0);
    CU_add_test(suite, "test of test_tokenizer_1()", test_tokenizer_1);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}