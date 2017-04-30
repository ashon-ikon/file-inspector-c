/* 
 * File:   test-file-manager.c
 * Author: y
 * 
 * Copyright (c) 2017 Yinka 
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
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include "test-file-manager.h"
#include "../../src/lib/util-string.h"

#define DIR_PATH_MAX  10240

FI_TEST_RESULT test_init()
{
    
    struct FiFileContainer *con = fi_file_container_init();
    
    char pwd[DIR_PATH_MAX];
    char *test_path = NULL;
    
    getcwd(pwd, DIR_PATH_MAX);
    test_path = fi_strconcat(2, pwd, "/test/fs/");
    
    fi_file_manager_read_dir(test_path, con, true);
    fi_return_fail_if_not(NULL != con, "Failed to create new container");

    fi_file_container_destroy(con);
    free(test_path);
    
    return FI_TEST_OKAY;
}


int main()
{
    FiTestFunc fi_tests [] = {
        {"test_init", test_init},
        {NULL, NULL} // THIS SHOULD ALWAYS BE THE LAST
    };
    
    return run(fi_tests);
}