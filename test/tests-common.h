/*
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

#ifndef FINSPECTOR_TESTS_COMMON_H
#define FINSPECTOR_TESTS_COMMON_H

#include <stdbool.h>

#include "./../src/lib/debug.h"

#ifdef __cplusplus
extern "C" {
#endif
    

typedef enum {
    FI_TEST_OKAY = 0,
    FI_TEST_FAIL = 10,
    FI_TEST_SKIPPED = 77,
    FI_TEST_LEAKED = 96,
    FI_TEST_CRITICAL = 99,
            
} FI_TEST_RESULT;
    
typedef FI_TEST_RESULT (*test_func) ();

#define fi_assert_true(con) ( (con) == true ? FI_TEST_OKAY : FI_TEST_FAIL)
#define fi_assert_fail(con) fi_assert_true(! (con) )
#define fi_return_if_fail(con) if (! fi_assert_true( (con) )) return FI_TEST_FAIL


#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_TESTS_COMMON_H */

