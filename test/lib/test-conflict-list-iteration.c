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


FI_TEST_RESULT test_conflict_group_creation()
{
    struct FiConfGroup *grp = fi_conflict_group_new();
    
    fi_return_fail_if_not(NULL != grp, "Failed to create conflict group list");

    fi_conflict_group_free(grp);

    return FI_TEST_OKAY;
}

FI_TEST_RESULT test_adding_files_to_conflict_group()
{
    struct FiConfGroup *grp = fi_conflict_group_new();
    
    struct FiFileInfo file1, file2;
    
    // Add some file information
    fi_file_init(&file1);
    fi_file_init(&file2);
    
    fi_conflict_group_add(grp, &file1);
    fi_conflict_group_add(grp, &file2);
    
    fi_return_fail_if_not(2 == fi_list_count(grp->files),
                        "Wrong number of items added");
    fi_conflict_group_free(grp);
    
    fi_file_destroy(&file1);
    fi_file_destroy(&file2);

    return FI_TEST_OKAY;
}

FI_TEST_RESULT test_checking_group_for_file()
{
    struct FiConfGroup *grp = fi_conflict_group_new();
    
    struct FiFileInfo file1, file2, file3, file4;
    
    fi_file_init(&file1);
    fi_file_init(&file2);
    fi_file_init(&file3);
    fi_file_init(&file4);

    fi_file_set_props(&file2,
            "IMAGE002",
            "/lorem/ipsum/",
            "tiff",
            (1024 * 63),
            (struct timespec){200, 300},
            file2.ref_count.free);
            
    fi_file_set_props(&file3,
            "IMAGE003",
            "/lorem/ipsum/",
            "tiff",
            (1024 * 63),
            (struct timespec){200, 300},
            file3.ref_count.free);
            
    fi_file_set_props(&file4,
            "IMAGE004",
            "/lorem/ipsum/",
            "tiff",
            (1024 * 63),
            (struct timespec){200, 300},
            file4.ref_count.free);

    
    fi_conflict_group_add(grp, &file1);
    fi_conflict_group_add(grp, &file2);
    fi_conflict_group_add(grp, &file4);
    
    
    fi_return_fail_if_not(fi_conflict_group_has(grp, &file4),
                        "Failed to find file 4 within group");
    
    fi_return_fail_if_not(! fi_conflict_group_has(grp, &file3),
                        "File 3 should NOT be part of the group");

    fi_file_destroy(&file1);
    fi_file_destroy(&file2);
    fi_file_destroy(&file3);
    fi_file_destroy(&file4);

    fi_conflict_group_free(grp);

    return FI_TEST_OKAY;
}


FI_TEST_RESULT test_conflict_groups_array_creation()
{
    struct FiFileConflictArray confl_array;
    fi_conflict_array_init(&confl_array);
    
    struct FiConfGroup *grp = fi_conflict_group_new();
    
    struct FiFileInfo file1, file2;

    fi_file_init(&file1);
    fi_file_init(&file2);
    
    fi_file_set_props(&file1,
            "IMAGE201",
            "/lorem/ipsum/",
            "tiff",
            (1024 * 256),
            (struct timespec){200, 300},
            file1.ref_count.free);
            
    fi_file_set_props(&file2,
            "IMAGE202",
            "/lorem/ipsum/",
            "tiff",
            (1024 * 184),
            (struct timespec){200, 300},
            file2.ref_count.free);
    
    fi_conflict_group_add(grp, &file1);
    fi_conflict_group_add(grp, &file2);
    
    fi_conflict_array_add_group(&confl_array, grp);
    
    fi_return_fail_if_not(2 == fi_list_count(grp->files),
                          "Wrong number of items added");
    
    fi_file_destroy(&file1);
    fi_file_destroy(&file2);
    fi_conflict_group_free(grp);

    fi_conflict_array_free(&confl_array);

    return FI_TEST_OKAY;
}


int main()
{
    FiTestFunc fi_tests [] = {
        {"test_conflict_group_creation", test_conflict_group_creation},
        {"test_adding_files_to_conflict_group", test_adding_files_to_conflict_group},
        {"test_checking_group_for_file", test_checking_group_for_file},
        {"test_conflict_groups_array_creation", test_conflict_groups_array_creation},
        {NULL, NULL} // THIS SHOULD ALWAYS BE THE LAST
    };
    
    return run(fi_tests);
}