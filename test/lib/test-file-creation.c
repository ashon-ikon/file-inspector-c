/* 
 * File:   test-file-creation.c
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
 * 
 */
#include "./../tests-common.h"

#include <stdio.h>
#include <locale.h>

#include "./../../src/lib/util-string.h"
#include "test-file-creation.h"

FI_TEST_RESULT test_file_info_creation()
{
    struct FiFileInfo file, file2;
    fi_file_init(&file);
    
    const char test_filename[]  =  "freak-zone.jpeg";
    const char test_path[]      =  "/home/lorem/workspace/";
    const char test_full_filename[] =  "/home/lorem/workspace/freak-zone.jpeg";
    
    file.full_filename  = fi_strdup(test_full_filename);
    file.path           = fi_strdup(test_path);
    file.filename       = fi_strdup(test_filename);
    file.type           = FI_FILE_TYPE_LINK;
    
    fi_file_init(&file2);
    fi_file_copy(&file, &file2);
   
    fi_return_fail_if_not(fi_strcmp0(file2.full_filename, test_full_filename),
                        fi_make_msg("We got %s", file2.full_filename));

    fi_return_fail_if_not(fi_strcmp0(file2.path, test_path),
                        fi_make_msg("We got %s", file2.path));
    
    fi_return_fail_if_not(fi_strcmp0(file2.filename, test_filename),
                        fi_make_msg("We got %s", file2.filename));
    
    fi_file_destroy(&file);
    fi_file_destroy(&file2);
    
    return FI_TEST_OKAY;
}

int main()
{
    FiTestFunc fi_tests [] = {
        {"test_file_info_creation", test_file_info_creation},
        FI_TEST_ENTRY_END
    };
    
    return run(fi_tests);
}
