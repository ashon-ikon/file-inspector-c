/* 
 * File:   array-test.c
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

#include "./../tests-common.h"
#include "array-test.h"


FI_TEST_RESULT test_array_simple_allocation()
{
    struct FiArray *arr = fi_array_new(sizeof(int), NULL);
    struct FiArray *arr_cpy = fi_array_new(sizeof(int), NULL);
    int t = 0;
    
    fi_array_push(arr, &t); t++;
    fi_return_if_fail(fi_array_get(arr, int, 0) == 0);
    
    fi_array_push(arr, &t); t++;
    fi_return_if_fail(fi_array_get(arr, int, 1) == 1);
    
    fi_array_push(arr, &t); t++;
    fi_return_if_fail(fi_array_get(arr, int, 2) == 2);
    
    fi_array_copy(arr, arr_cpy);
    fi_return_if_fail(fi_array_size(arr) == fi_array_size(arr_cpy));
    
    
    fi_array_push(arr_cpy, &t);
    fi_return_if_fail(fi_array_get(arr, int, 3) == 3);
    
    t = 1000;
    fi_array_insert(arr_cpy, &t, 2);
    fi_return_if_fail(fi_array_get(arr_cpy, int, 2) == 1000);

    fi_return_if_fail(*fi_array_get_ptr(arr_cpy, int, 2) == 1000);

    fi_array_destroy(arr);
    fi_array_destroy(arr_cpy);
    
    return FI_TEST_OKAY;
}