/**
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
 * 
 */

#include <stdbool.h>
#include <stddef.h>         // defines NULL
#include <stdlib.h>         // malloc
#include <stdio.h>
#include <stdarg.h>
#include "detector-private.h"
#include "string-helper.h"

/* This is the minimum items in list to start with 
 */
#define FILE_LIST_ALLOC_CHUNK_SIZE 20

/**
 * Returns an empty
 * @return FiFileList
 */
static FiFileList *
fi_file_list_new ()
{
    // Initialize stuct
    FiFileList * list = malloc(sizeof (FiFileList) + sizeof (FiFileInfo **));
    if (NULL == list) {
        fi_print_error("Failed to allocate initial memory");
        return NULL;
    }
    list->length = 0;
    list->capacity = 0;
    list->pfile_info_list = NULL;    
    // We attempt to pre-allocate memory to avoid subsequent cost
    if (FI_SUCCESS != resize_list_if_required(list, 1)) {
        fi_print_error("Failed to allocate enough new memory");
        return NULL;
    }

    return list;
}

static FiFileList *
fi_file_list_add (FiFileList * self, FiFileInfo * file_info)
{
    // Scale up size if required
    if (NULL == self || FI_SUCCESS != resize_list_if_required(self, 1))
        return NULL;

    // Set the data
    self->pfile_info_list[self->length++] = file_info;
    
    return self;
}

static FiReturnResponse
resize_list_if_required(FiFileList * list, size_t size)
{
    FiFileInfo ** pfile_info_list;
    if (! list) {
        return FI_ERROR_NULL_VALUE;
    }
    // Scale up size if required
    if ((list->length + size) > list->capacity) {
        if (list->capacity == 0) {
            // This is possibly the first initialization
            // we need to scale appropriately
            pfile_info_list = 
                malloc((list->capacity + FILE_LIST_ALLOC_CHUNK_SIZE) * sizeof (FiFileInfo **)); /* (FiFileInfo **) */
        } else {
            // Current capacity can't contain the desired data, we need to
            // scale up to the next block of data
            pfile_info_list = 
                realloc( list->pfile_info_list,
                    (list->capacity + FILE_LIST_ALLOC_CHUNK_SIZE) * sizeof (FiFileInfo **)); /* (FiFileInfo **) */

        }
        // Validate the allocation
        if (!pfile_info_list) {
            fi_print_error("Failed to allocate memory for new data."
                    "(Length %d, Capacity: %d)", list->length, list->capacity);
            return FI_ERROR_OUT_OF_MEM;
        }
        list->pfile_info_list = pfile_info_list; // It's good to use
        // We need to warm the memory to predefined state
        for (size_t l = list->length; l < (list->capacity); l++) {
printf("Clearing %llu\n", (unsigned long long) l);
            list->pfile_info_list[list->length] = NULL; // Clear out the space
        }
        list->capacity += FILE_LIST_ALLOC_CHUNK_SIZE;
    }
    
    return FI_SUCCESS;
}


static bool
fi_file_list_free (FiFileList * self)
{
    if (NULL != self->pfile_info_list || self->length) {
        for (uint64_t i = 0; i < self->length; i++) {
            FiFileInfo *p_info = self->pfile_info_list[i];
            // Free the structure
            free(p_info->file_extension);
            free(p_info->file_path);
            free(p_info->filename);
        }
        // Free the array holder
        free (self->pfile_info_list);
    }
    
    self->capacity = 0;
    self->length = 0;
    
    // Free self
    free (self);
    return true;
}

/**x
 * Handy method to print error messages
 * @param err
 */
static void
fi_print_error(const char * err, ...)
{

    va_list ap;
    va_start(ap, err);
    char * ae = fi_vsstrdup(err, ap);
    va_end(ap);
    
    fprintf(stderr, "Error: %s\n", ae);    
    // Free the memory
    free(ae);
}

void do_this() {
    FiFileList * list = fi_file_list_new();
    FiFileInfo info, info1;
    info.file_extension = fi_strdup("jpeg");
    info.file_path = fi_strdup("/home/yasonibare/Workshop/C-something");
    info.file_type = FI_FILE_TYPE_REGULAR;
    info.filename = fi_strdup("my_custom_file");

    info1.file_extension = fi_strdup("txt");
    info1.file_path = fi_strdup("/home/yasonibare/Workshop/D-something");
    info1.file_type = FI_FILE_TYPE_REGULAR;
    info1.filename = fi_strdup("lorem_file");

    fi_file_list_add(list, &info);
    fi_file_list_add(list, &info1);
    fi_print_error("Failed to allocate memory for new data."
                   " (Length %d, Capacity: %d)", list->length, list->capacity);
    FiFileInfo **v = NULL;
    v = list->pfile_info_list;
    for (size_t i = 0; i < list->length; i++) {
        printf("Filename: %s\n", list->pfile_info_list[i]->filename);
    }
    fi_file_list_free(list);
}