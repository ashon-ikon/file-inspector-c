/* 
 * File:   test-suite.c
 * Author: yasonibare
 * 
 * Copyright (c) 2016 Yinka Asonibare
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
 * 
 */
#include <stdio.h>
#include <locale.h>

#include "tests-common.h"
#include "lib/test-array.h"
#include "lib/test-file-creation.h"

#define MAX_MSG     512
#define OUTCOME     32
#define FI_REASON_MAX 50

char reason_buff[FI_REASON_MAX];
extern char *fi_got_msg(char *fmt, ...) fi_checkprintf;

void print_test_outcome(char *test_name, char *result)
{
    char msg_output[MAX_MSG];
    snprintf(msg_output, MAX_MSG - 2, "Test %s : %s\n", test_name, result);
    printf(msg_output);
}

int run(FiTestFunc *tests)
{
    // Set the default locale
    setlocale(LC_CTYPE, "");
    
    int test_count = 0;
    int successful = 0;
    int failed     = 0;
    int skipped    = 0;

    for (; tests[test_count].test; test_count++) {
        test_func test = tests[test_count].test;
        char *test_name = tests[test_count].name;
        switch ( test() ) {
        case FI_TEST_OKAY:
            print_test_outcome(test_name, "passed");
            successful++;
            break;
        case FI_TEST_SKIPPED:
            print_test_outcome(test_name, "skipped !");
            skipped++;
            break;
        case FI_TEST_FAIL:
            print_test_outcome(test_name, "failed !");
            failed++;
            break;
        default:
            print_test_outcome(test_name, "<UNKNOWN>!!");
            break;
        }
    }
    
    printf("\nTest summary\n\n"
           "Total %d test%s,\t%d skipped\t%d failed\t%d passed\n\n",
            test_count, (test_count > 1? "s": ""), skipped, failed, successful);
    

    return 0;
}

char *fi_got_msg(char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(reason_buff, FI_REASON_MAX - 2, fmt, ap);
    va_end(ap);
    
    reason_buff[FI_REASON_MAX -1] = '\0';
    
    return reason_buff;
}

