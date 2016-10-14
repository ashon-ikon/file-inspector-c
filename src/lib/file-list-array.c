/* 
 * File:   file-list-array.c
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
#include <stdarg.h>         // vargs
#include <stdbool.h>
#include <stddef.h>         // defines NULL
#include <stdlib.h>         // malloc
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "debug.h"
#include "file-list-array.h"

/* This is the minimum items in list to start with 
 */
#define FILE_LIST_ALLOC_CHUNK_SIZE 20

/**
 * Returns an empty
 * @return FiFileList
 */
FiFileList *
fi_file_list_new ()
{
    // Initialize stuct
    FiFileList * list = malloc(sizeof (FiFileList));
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

/**
 * Prints the contents of the file info
 * @param info
 */
void
fi_file_info_print_content(const FiFileInfo* info)
{
    const char *type[FI_NUM_OF_FILE_TYPES] = {
        "Unmapped Type",
        "Directory",
        "File",
        "Link",
    };
    int key = 0;
    switch (info->file_type) {
        case FI_FILE_TYPE_DIRECTORY:
            key = 1;
            break;
        case FI_FILE_TYPE_REGULAR:
            key = 2;
            break;
        case FI_FILE_TYPE_LINK:
            key = 3;
            break;
        default:
            key = 0;
            break;
    }
    printf("(D) Path: '%s'\tFilename: '%s'\tType: %s\tExtension: '%s'\n",
           info->file_path, info->filename, type[key], info->file_extension);
            
}

FiFileList *
fi_file_list_add (FiFileList * list, FiFileInfo * file_info)
{
    // Scale up size if required
    if (NULL == list  || FI_SUCCESS != resize_list_if_required(list, 1))   {
        fi_print_error("Not enough memory to store data");
        return NULL;
    }

    // Set the data
    fi_file_info_copy(&list->pfile_info_list[list->length++], file_info);

    return list;
}

FiReturnResponse
resize_list_if_required(FiFileList * list, size_t size)
{
    FiFileInfo ** pfile_info_list;
    if (NULL == list) {
        return FI_ERROR_NULL_VALUE;
    }
    // Scale up size if required
    if ((list->length + size) > list->capacity) {
        if (list->capacity == 0) {
            // This is possibly the first initialization
            // we need to scale appropriately
            pfile_info_list = 
                malloc((list->capacity + FILE_LIST_ALLOC_CHUNK_SIZE) * sizeof (FiFileInfo *)); /* (FiFileInfo **) */
        } else {
            // Current capacity can't contain the desired data, we need to
            // scale up to the next block of data
            pfile_info_list = 
                realloc( list->pfile_info_list,
                    (list->capacity + FILE_LIST_ALLOC_CHUNK_SIZE) * sizeof (FiFileInfo *)); /* (FiFileInfo **) */

        }
        // Validate the allocation
        if (NULL == pfile_info_list) {
            fi_print_error("Failed to allocate memory for new data."
                    "(Length %d, Capacity: %d)", list->length, list->capacity);
            return FI_ERROR_OUT_OF_MEM;
        }
        list->pfile_info_list = pfile_info_list; // It's good to use
        list->capacity += FILE_LIST_ALLOC_CHUNK_SIZE;
        // We need to warm the memory to predefined state
        for (size_t l = list->length; l < (list->capacity); l++) {
            list->pfile_info_list[list->length] = NULL; // Clear out the space
        }
    }
    
    return FI_SUCCESS;
}

FiFileInfo *
fi_file_info_copy (FiFileInfo ** dest, const FiFileInfo * src)
{
    FiFileInfo *tmp = malloc (sizeof (*tmp));
    if (NULL == tmp) {
        fi_print_error("Failed to allocate enough memory for copy");
        return NULL;
    }
    
    tmp->file_extension = strdup (src->file_extension);
    tmp->file_path      = strdup (src->file_path);
    tmp->filename       = strdup (src->filename);
    tmp->file_type      = src->file_type;
    
    *dest = tmp;
    
    return *dest;
}

bool
fi_file_list_free (FiFileList * list)
{
    if (list->length) {
        // Free each file info
        for (uint64_t i = 0; i < list->length; i++)
            fi_file_info_free(list->pfile_info_list[i]);

        // Free the array holder
        free (list->pfile_info_list);
    }
    
    list->capacity = 0;
    list->length = 0;
    
    // Free list
    free (list);

    return true;
}

void
fi_file_info_free (FiFileInfo *p_info)
{
    if (NULL != p_info) {
        // Free the structure
        if (p_info->file_extension != NULL) free(p_info->file_extension);
        if (p_info->file_path != NULL) free(p_info->file_path);
        if (p_info->filename != NULL) free(p_info->filename);
        
        free(p_info);
    }
}