/* 
 * File:   test-list-iteration.c
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
 */

#include "test-list-iteration.h"


FI_TEST_RESULT test_list_creation()
{
    struct FiList *list = fi_list_new(NULL, NULL);
    
    fi_return_if_fail(NULL != list, "Failed to create new list");

    fi_list_free(list);
    
    return FI_TEST_OKAY;
}

#define LIST_COUNT 5
FI_TEST_RESULT test_list_append()
{
    struct FiList *list = fi_list_new(NULL, NULL);
    
    fi_return_if_fail(NULL != list, "Failed to create list");
    
    for (unsigned char i = 0; i < LIST_COUNT; i++) {
        struct FiList *li = fi_list_new(NULL, NULL);
        fi_list_append(list, li);

        fi_return_if_fail(fi_list_count(li) == (i + 2), // One added before
            fi_got_msg("Wrong count of items in a list. Got %d, Expected %d",
                fi_list_count(li), (i + 2)
            ));
    }

    fi_list_free(list);
    
    return FI_TEST_OKAY;
}

FI_TEST_RESULT test_list_prepend()
{
    struct FiList *list = fi_list_new(NULL, NULL);
    
    fi_return_if_fail(NULL != list, "Failed to create list");
    
    for (unsigned char i = 0; i < LIST_COUNT; i++) {
        struct FiList *li = fi_list_new(NULL, NULL);
        fi_list_prepend(list, li);

        fi_return_if_fail(fi_list_count(li) == (i + 2), // One added before
            fi_got_msg("Wrong count of items in a list. Got %d, Expected %d",
                fi_list_count(li), (i + 2)
            ));
    }

    fi_list_free(list);
    
    return FI_TEST_OKAY;
}

int main()
{
    FiTestFunc fi_tests [] = {
        {"test_list_creation", test_list_creation},
        {"test_list_append", test_list_append},
        {NULL, NULL} // THIS SHOULD ALWAYS BE THE LAST
    };
    
    return run(fi_tests);
}