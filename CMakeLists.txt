cmake_minimum_required(VERSION 3.28)
project(Tokenizer C)

set(CMAKE_C_STANDARD 11)

add_executable(raw_tokenizer_test
        tests/raw_tokenizer_test.c
        tokenizer/raw_tokenizer.c
        tokenizer/classified_tokenizer.c
        tests/classified_tokenizer_test.c
)

add_executable(classified_tokenizer_test
        tests/classified_tokenizer_test.c
        tokenizer/classified_tokenizer.c
        tokenizer/raw_tokenizer.c
        tokenizer/classified_tokenizer.c
)
