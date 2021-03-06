/* 
 * File:   file-inspector.c
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
 * Created on 28 August 2016, 10:42 PM
 */

#include "./../common.h"

#include <locale.h>
#include <stdlib.h>
#include <stdio.h>

#include "file-inspector.h"

/**
 * Runs the file inspector as a CLI application
 * @param argc
 * @param argv
 */
int run_with_params(int argc, char * argv[]);
void run_inspector();

int main(int argc, char * argv[])
{
        // Set the default locale
        setlocale(LC_CTYPE, "");

        if (argc > 1) {
                return run_with_params(argc, argv);
        }

        run_inspector();

        return 0;
}

int run_with_params(int argc, char * argv[])
{
        return 0;
}

void run_inspector()
{
        struct FiFileContainer *files = fi_file_container_init();

        fi_file_manager_read_dir("/home/yasonibare/Workspace/C-C++/", files, true);
 
//        struct FiFileConflictArray *pConflicts = NULL;
//        fi_algo_extract_duplicate(files, pConflicts);

        size_t c = fi_file_container_size(files);
        printf("We got %s many %s %zu\n", (c > 1 ? "these" : "this"), (c > 1 ? "files" : "file"), c);

//        fi_conflict_array_free(pConflicts);
        fi_file_container_destroy(files);
}
