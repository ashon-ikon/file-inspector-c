/*
 * File:   file-container.c
 * Author: Yinka Ashon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
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
#include <stdlib.h>

#include "lib-common.h"
#include "file-container.h"



/**
 * Initializes the file array
 * @param array
 */
struct FiFileContainer *fi_file_container_init()
{
    struct FiFileContainer *container = malloc(sizeof *container);
    
    if (! container)
        return NULL;

    container->array = fi_array_new(sizeof (struct FiFileInfo),
                                    fi_file_copy_proxy);
    
    if (! container->array) {
        fi_log_message(FI_DEBUG_LEVEL_ERROR,
                       "Failed to allocate container array memory");
        free(container);
        return NULL;
    }

    return container;
}

void fi_file_container_destroy(struct FiFileContainer *container)
{
    if (! container)
        return;

    struct FiFileInfo *file = NULL;
    fi_array_each(container->array, struct FiFileInfo, file) {
        fi_file_destroy(file);
    }

    fi_array_ref_dec(&container->array->ref_count);

    free(container);
}

/**
 * @param arr
 * @param info
 * @return 
 */
unsigned short fi_file_container_push(struct FiFileContainer *arr,
                                      struct FiFileInfo  *info)
{
    if (! info || ! arr)
        return FI_FUNC_FAIL;

    return fi_array_push(arr->array, info);    
}

/* ------------------------------------------------------------------
 * ------------------------------------------------------------------
 * Traversing
 */

/**
 * Returns File Info structure
 * 
 * return value must be freed with "fi_file_info_value_cleanup" !
 * @param arr
 * @param i
 * @return FileInfo
 */
struct FiFileInfo *fi_file_container_get_at(struct FiFileContainer *con, unsigned long i)
{
    if (! con)
        return NULL;

    if (i < 0 || i > fi_file_container_size(con))
        return NULL;

    struct FiFileInfo *file = fi_array_get_ptr(con->array,
                                               struct FiFileInfo, i);
    fi_ref_inc(&file->ref_count);
    
    return file;   
}

struct FiFileInfo *fi_file_container_get_begin(struct FiFileContainer *con)
{    
    struct FiFileInfo *file = fi_array_get_ptr_being(con->array,
                                                     struct FiFileInfo);
    if (file)
        fi_ref_inc(&file->ref_count);
    
    return file;
}


struct FiFileInfo *fi_file_container_get_next(struct FiFileContainer *con)
{
    struct FiFileInfo *file = fi_array_get_ptr_next(con->array,
                                                    struct FiFileInfo);
    if (file)
        fi_ref_inc(&file->ref_count);
    
    return file;
}

struct FiFileInfo *fi_file_container_get_end(struct FiFileContainer *con)
{
    struct FiFileInfo *file = fi_array_get_ptr_end(con->array,
                                                   struct FiFileInfo);
    if (file)
        fi_ref_inc(&file->ref_count);
    
    return file;
}
