/* 
 * File:   file-list-array.h
 * Author: Yinka Ashon
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
 * Created on 4 October 2016, 9:30 PM
 */

#ifndef FILE_LIST_ARRAY_H
#define FILE_LIST_ARRAY_H

#include <stdbool.h>

#include "lib-common.h"
#include "detector-private.h"
#include "file-list-array.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Returns an empty
 * @return FiFileList
 */
FiFileList *
fi_file_list_new ();

FiFileList *
fi_file_list_add (FiFileList * list, FiFileInfo * file_info);

bool
fi_file_list_free (FiFileList * list);

FiFileInfo *
fi_file_info_copy (FiFileInfo ** dest, const FiFileInfo * src);

void
fi_file_info_free(FiFileInfo *pinfo);

FiReturnResponse
resize_list_if_required(FiFileList * list, size_t size);

void
fi_file_info_print_content(const FiFileInfo* info);

#ifdef __cplusplus
}
#endif

#endif /* FILE_LIST_ARRAY_H */

