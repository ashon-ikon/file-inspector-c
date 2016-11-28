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

//
//#define FILE_COUNT      3
//static void add_files_to_create_outside(struct FiFileContainer *con)
//{
//    for (int i = 0; i < FILE_COUNT; i++) {
//        struct FiFileInfo file;
//        fi_file_init(&file);
//        
//        file.extension = fi_strdup(".docx");
//        file.path      = fi_strdup("/home/lorem/ipsum/");
//        file.filename       = fi_strdup("oh_praise_him");
//        file.type      = FI_FILE_TYPE_REGULAR;
//    
//        fi_file_container_push(con, &file);
//        
//        // free the memory
//        fi_file_destroy(&file);
//        
//    }
//}
//
//FI_TEST_RESULT test_file_container_push_data()
//{
//    struct FiFileContainer *con = fi_file_container_init();
//    
//    fi_return_if_fail(NULL != con, "Failed to create container");
//    
//    add_files_to_create_outside(con);
//    
//    fi_return_if_fail(fi_file_container_size(con) == FILE_COUNT,
//                      "Wrong number of files added");
//    struct FiFileInfo *file = NULL;
//    fi_container_each(con, file) {
//        fi_return_if_fail(strcmp(file->extension, ".docx") == 0,
//                        fi_got_msg("We got %s", file->extension));
//    }
//    
//    // Free the 
//    fi_file_container_destroy(con);
//    
//    return FI_TEST_OKAY;
//}

int main()
{
    FiTestFunc fi_tests [] = {
        {"test_list_creation", test_list_creation},
        {"test_list_append", test_list_append},
        {NULL, NULL} // THIS SHOULD ALWAYS BE THE LAST
    };
    
    return run(fi_tests);
}