/* 
 * File:   test-array.c
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

#include "test-array.h"


FI_TEST_RESULT test_array_simple_allocation()
{
    struct FiArray *arr = fi_array_new(sizeof(int), NULL);
    struct FiArray *arr_cpy = fi_array_new(sizeof(int), NULL);
    int t = 0;
    
    fi_array_push(arr, &t); t++;
    fi_return_fail_if_not(fi_array_get(arr, int, 0) == 0,
                        fi_got_msg("We got %d", fi_array_get(arr, int, 0)));
    
    fi_array_push(arr, &t); t++;
    fi_return_fail_if_not(fi_array_get(arr, int, 1) == 1,
                        fi_got_msg("We got %d", fi_array_get(arr, int, 1)));
    
    fi_array_push(arr, &t); t++;
    fi_return_fail_if_not(fi_array_get(arr, int, 2) == 2,
                        fi_got_msg("We got %d", fi_array_get(arr, int, 2)));
    
    fi_array_copy(arr, arr_cpy);
    fi_return_fail_if_not(fi_array_size(arr) == fi_array_size(arr_cpy),
            "Wrong number of data copied!");
    
    
    fi_array_push(arr_cpy, &t);
    fi_return_fail_if_not(fi_array_get(arr_cpy, int, 3) == 3,
                        fi_got_msg("We got %d", fi_array_get(arr_cpy, int, 3)));
    
    t = 1000;
    fi_array_insert(arr_cpy, &t, 2);
    fi_return_fail_if_not(fi_array_get(arr_cpy, int, 2) == 1000,
                        fi_got_msg("We got %d", fi_array_get(arr, int, 2)));

    fi_return_fail_if_not(*fi_array_get_ptr(arr_cpy, int, 2) == 1000,
                        fi_got_msg("We got %d", *fi_array_get_ptr(arr, int, 2)));

    fi_array_destroy(arr);
    fi_array_destroy(arr_cpy);
    
    return FI_TEST_OKAY;
}

FI_TEST_RESULT test_array_each_loop()
{
    struct FiArray *arr = fi_array_new(sizeof(int), NULL);
    int t = 0;
    
    for (t = 200; t < 203; t++)
        fi_array_push(arr, &t);
    
    t = 200;
    
    int *p = NULL;
    fi_array_each(arr, int, p) {
        fi_return_fail_if_not(t++ == *p,
            fi_got_msg("We got %d, instead of %d", *p, (t - 1)));
    }
    
    fi_array_destroy(arr);
    
    return FI_TEST_OKAY;
}

int main()
{
    FiTestFunc fi_tests [] = {
        {"test_array_simple_allocation", test_array_simple_allocation},
        {"test_array_each_loop",         test_array_each_loop},
        {NULL, NULL} // THIS SHOULD ALWAYS BE THE LAST
    };
    
    return run(fi_tests);
}