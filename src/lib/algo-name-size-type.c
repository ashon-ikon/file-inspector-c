/* 
 * File:   algo-name-size-type.c
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
 */

#include <math.h>
#ifdef HAVE__BOOL
#include <stdbool.h>
#endif

#include "algo-name-size-type.h"
#include "file.h"
#include "file-container.h"
#include "file-hash.h"
#include "util-string.h"


#define FILE_SIZE_TOLERANCE             (4) /* How much of bytes difference */
                                            /* should be consider equal */
#define FILE_CONTENT_READ_AMOUNT        (1024)

static bool check_file_matches(struct FiFileInfo *fileA, struct FiFileInfo *fileB);

#include <stdio.h>
int fi_algo_extract_duplicate(struct FiFileContainer *files,
                              struct FiFileConflictArray   *conflicts)
{
        size_t total = 0;
        struct FiFileInfo *file, *check;
        total = fi_file_container_size(files);

        for (size_t i = 0; i < total; i++) {
                // Grab the test file
                file = fi_file_container_get_file_at(files, i);
                
                for (size_t j = 0; j < total; j++) {
                        if (i == j)
                                continue;
                        check = fi_file_container_get_file_at(files, j);
                        if (check_file_matches(file, check)) {
//                                // Add to the duplicates for `file`
//                                printf("%s/%s (%zu) duplicate found in %s/%s (%zu)\n", file->path, file->filename, file->size_byte, check->path, check->filename, check->size_byte);
//                                
                        }
                }
        }
        return FI_FUNC_SUCCESS;
}


static bool check_file_matches(struct FiFileInfo *file_a, struct FiFileInfo *file_b)
{
        if (!file_a || !file_b)
                return false;
        
        if (file_a->type == FI_FILE_TYPE_DIRECTORY)
                return false;
        
        if (file_b->type == FI_FILE_TYPE_DIRECTORY)
                return false;
        
        if (file_a->type != file_b->type)
                return false;
        
        if (abs(file_a->size_byte - file_b->size_byte) > FILE_SIZE_TOLERANCE)
                return false;

        if (!fi_strcmp0(fi_file_get_extension(file_a), fi_file_get_extension(file_b)))
                return false;
        
        if (fi_strcmp0(file_a->filename, file_b->filename)) {
                return true;
        } else {
                // Handle possibly similar filename
//                printf("A: %lu, B: %lu\n", fi_hash_data("First value", 11), fi_hash_data("Second long value", 17));
        }
        
        return true;
}
