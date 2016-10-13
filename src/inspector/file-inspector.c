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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "file-inspector.h"
#include "src/lib/detector.h"
#include "src/lib/file-list-array.h"

int
main(int argc, char* argv[])
{
    // Set the default locale
    setlocale(LC_CTYPE, "");
    
    char* src = fi_strdup("/home/yasonibare/Workspace/C-C++/file-inspector-c/test");
    char* dest = strdup("/home/yasonibare/Downloads/dump");

    FiFileList* src_list = fi_file_list_get_list_from_source_m(src, true);
    // Free resources...
    fi_file_list_free(src_list);
    free(src);
    free(dest);
    
    return 0;
}
