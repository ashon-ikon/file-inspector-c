/* 
 * File:   test-list-iteration.c
 * Author: Yinka Ashon
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

#include <string.h>

#include "test-list-iteration.h"


FI_TEST_RESULT test_list_creation()
{
    struct FiList *list = fi_list_new(NULL, NULL);
    
    fi_return_fail_if_not(NULL != list, "Failed to create new list");

    fi_list_free(list);
    
    return FI_TEST_OKAY;
}

#define LIST_COUNT 5
FI_TEST_RESULT test_list_append()
{
    struct FiList *list = fi_list_new(NULL, NULL);

    for (unsigned char i = 0; i < LIST_COUNT; i++) {
        struct FiList *li = fi_list_new(NULL, NULL);
        fi_list_append(list, li);

        fi_return_fail_if_not(fi_list_count(li) == (i + 2), // One added before
            fi_make_msg("Wrong count of items in a list. Got %d, Expected %d",
                fi_list_count(li), (i + 2)
            ));
    }

    fi_list_free(list);
    
    return FI_TEST_OKAY;
}

FI_TEST_RESULT test_list_prepend()
{
    struct FiList *list = fi_list_new(NULL, NULL);
    
    for (unsigned char i = 0; i < LIST_COUNT; i++) {
        struct FiList *li = fi_list_new(NULL, NULL);
        fi_list_prepend(list, li);

        fi_return_fail_if_not(fi_list_count(li) == (i + 2), // One added before
            fi_make_msg("Wrong count of items in a list. Got %d, Expected %d",
                fi_list_count(li), (i + 2)
            ));
    }

    fi_list_free(list);
    
    return FI_TEST_OKAY;
}

FI_TEST_RESULT test_list_iteration()
{
    int    var[LIST_COUNT + 1], t = 0, *pint = NULL;
    var[0] = 10;
    struct FiList *list = fi_list_new(var, NULL);
    
    struct FiList *li = NULL;
    for (unsigned char i = 1; i < LIST_COUNT + 1; i++) {
        var[i] = i + 10;
        li = fi_list_new(var + i, NULL);
        fi_list_prepend(list, li);
    }

    t  = 15;
    for (li = list; li->prev; li = li->prev);
    // Got the other direction
    for (; li != NULL; li = li->next ) {
        
        pint = fi_list_data_ptr(li, int);
        fi_return_fail_if_not(*pint == t--,
            fi_make_msg("Failed to get stored value. Got %d, Expected %d",
                *pint, t
            ));
    }
    
    fi_list_free(list);
    
    return FI_TEST_OKAY;
}

static char data_buff[13]; // 6 x 2 + '\0'
static void each_callback(void *data)
{
    char num[3];
    itoa(*(int *)data, num, 10);
    strncat(data_buff, num, 2);
}

FI_TEST_RESULT test_list_each_func()
{
    int    var[LIST_COUNT + 1];
    var[0] = 10;
    struct FiList *list = fi_list_new(var, NULL);
    
    struct FiList *li = NULL;
    for (unsigned char i = 1; i < LIST_COUNT + 1; i++) {
        var[i] = i + 10;
        li = fi_list_new(var + i, NULL);
        fi_list_prepend(list, li);
    }

    data_buff[0] = '\0'; // Zero out the string
    fi_list_each(list, each_callback);
    fi_return_fail_if_not(12 == strlen(data_buff),
        fi_make_msg("Foreach method is faulty. Got %lu, Expected %d",
            strlen(data_buff), 12
        ));
    
    fi_list_free(list);
    
    return FI_TEST_OKAY;
}


int main()
{
    FiTestFunc fi_tests [] = {
        {"test_list_creation", test_list_creation},
        {"test_list_append", test_list_append},
        {"test_list_prepend", test_list_prepend},
        {"test_list_iteration", test_list_iteration},
        FI_TEST_ENTRY_END
    };
    
    return run(fi_tests);
}
