/* 
 * File:   test-conflict-list-iteration.c
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

#include "test-conflict-list-iteration.h"


FI_TEST_RESULT test_conflict_list_creation()
{
#define TestName "Test Conflict"
    struct FiConflictList *conflict = fi_conflict_new(TestName);
    
    fi_return_if_fail(NULL != conflict, "Failed to create conflict contianer");

    fi_return_if_fail(fi_strcmp0(conflict->name, TestName),
                       "Failed to create conflict contianer");
    
    fi_conflict_destroy(conflict);
    
    return FI_TEST_OKAY;
}

int main()
{
    FiTestFunc fi_tests [] = {
        {"test_conflict_list_creation", test_conflict_list_creation},
        {NULL, NULL} // THIS SHOULD ALWAYS BE THE LAST
    };
    
    return run(fi_tests);
}