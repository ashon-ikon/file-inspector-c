/*
 * File:   file-array.c
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
#include <stdlib.h>
#include <malloc.h>

#include "file.h"
#include "util-string.h"

const struct FiFileInfo EMPTY_FILE = {  
    NULL,      /* filename */
    NULL,      /* file_path */
    NULL,      /* file_extension */
    0L,        /* size */
    0,         /* file_type */
   {0, 0},     /* struct timespec */
   {0, NULL}   /* struct FiRef */
};

/* Prototypes */
static void fi_file_info_ref_destory(const struct FiRef *ref);

/**
 * Initializes file info structure
 * @param file
 */
void fi_file_init(struct FiFileInfo  *file)
{
    if (! file)
        return;

    *file = EMPTY_FILE;
}

/**
 * Free the resources
 * @param file
 */
void fi_file_destroy(struct FiFileInfo * file)
{
    if (! file)
        return;

    free(file->filename);
    free(file->file_path);
    free(file->file_extension);

}

bool fi_file_copy_proxy(void const *src, void *dst, unsigned n)
{
    if (! src || ! dst)
        return false;
    
    if (n != sizeof(struct FiFileInfo)) {
        fi_log_message(FI_DEBUG_LEVEL_WARN,
            "Failed to copy data. Size mismatch. Expected %u, got %d",
            sizeof (struct FiFileInfo), n);
        return false;
    }
    
    return fi_file_copy((struct FiFileInfo *)src, (struct FiFileInfo*) dst);
}

/**
 * Duplicates the file information
 * ** Remember to destroy copy
 * @param src
 * @param dest
 */
bool fi_file_copy(const FiFileInfo_st *src, FiFileInfo_st *dest)
{
    if (! src || ! dest)
        return false;

    dest->filename       = fi_strndup(src->filename, strlen(src->filename));
    dest->file_path      = fi_strndup(src->file_path, strlen(src->file_path));
    dest->file_extension = fi_strndup(src->file_extension,
                                      strlen(src->file_extension));
    dest->size_byte      = src->size_byte;
    dest->modified_at    = src->modified_at;
    dest->ref_count.free = src->ref_count.free;
    fi_ref_inc(&dest->ref_count);

    return true;
}


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
        fi_log_message(FI_DEBUG_LEVEL_CRITICAL,
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

    fi_array_destroy(container->array);

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

    return fi_array_get_ptr(con->array, struct FiFileInfo, i);
}

struct FiFileInfo *fi_file_container_get_begin(struct FiFileContainer *con)
{    
    return fi_array_get_ptr_being(con->array, struct FiFileInfo);
}


struct FiFileInfo *fi_file_container_get_next(struct FiFileContainer *con)
{
    return fi_array_get_ptr_next(con->array, struct FiFileInfo);
}

struct FiFileInfo *fi_file_container_get_end(struct FiFileContainer *con)
{
    return fi_array_get_ptr_end(con->array, struct FiFileInfo);
}
