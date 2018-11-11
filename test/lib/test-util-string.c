/* 
 * File:   test-util-string.c
 * Author: Yinka Asonibare
 * 
 * Copyright (c) 2016-2018 Yinka Ashon
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is furnished 
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "./../tests-common.h"

#include <stdio.h>
#include <stdbool.h>

#include "test-util-string.h"

FI_TEST_RESULT test_string_empty()
{
    char *no_str = NULL;
    char *empty = fi_strdup(no_str);
    fi_return_fail_if_not(NULL == empty, "String should be empty");
    
    fi_return_fail_if_not(fi_strlen(no_str) == 0, "String length should be '0' ");

    return FI_TEST_OKAY;
}

static FI_TEST_RESULT run_string_dup_test(const char *str, const char *expected)
{
    fi_return_fail_if_not(NULL != str, "Failed to create string");
    
    bool same = strlen(expected) == fi_strlen(str);
    bool same_com = strcmp(expected, str) == 0;
    
    fi_return_fail_if_not(same, "String duplication failed");
    fi_return_fail_if_not(same_com, "String duplication failed");
    
    return FI_TEST_OKAY;
}

FI_TEST_RESULT test_string_duplication()
{
    const char word1[] = "Lorem ipsum";

    char *new_string = fi_strdup(word1);
    FI_TEST_RESULT r = run_string_dup_test(new_string, word1);
    free (new_string);
    
    return r;
}

FI_TEST_RESULT test_string_duplication_with_length()
{
    const char word1[] = "Lorem ipsum";

    char *new_string = fi_strndup(word1, fi_strlen(word1));
    
    FI_TEST_RESULT r = run_string_dup_test(new_string, word1);
    free (new_string);
    
    return r;
}

FI_TEST_RESULT test_string_concatenation()
{
    const char word1[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,";
    const char word2[] = "sed do eiusmod tempor incididunt ut labore et dolore ";
    const char word3[] = "Sed ut perspiciatis unde omnis iste natus ";

    char * new_string = fi_strconcat(3, word1, word2, word3);
    fi_return_fail_if_not(NULL != new_string, "Failed to create string");

    free (new_string);
    
    return FI_TEST_OKAY;
}

int main()
{
    FiTestFunc fi_tests [] = {
        {"test_string_concatenation", test_string_concatenation},
        {"test_string_empty",         test_string_empty},
        {"test_string_duplication",   test_string_duplication},
        {"test_string_duplication_with_length", test_string_duplication_with_length},
        FI_TEST_ENTRY_END
    };
    
    return run(fi_tests);
}