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

const struct FiFileInfo EMPTY_FILE = { NULL, NULL, NULL, 0L, 0, {0, 0}};

/* Prototypes */
static void fi_file_init(FiFileInfo_st *file);
static void fi_file_destroy(FiFileInfo_st *file);
static void fi_file_copy(const FiFileInfo_st *src, FiFileInfo_st *dest);

/**
 * Initializes file info structure
 * @param file
 */
static void fi_file_init(FiFileInfo_st  * file)
{
    if (! file)
        return;

    *file = EMPTY_FILE;
}

/**
 * Free the resources
 * @param file
 */
static void fi_file_destroy(struct FiFileInfo * file)
{
    if (! file)
        return;

    free(file->filename);
    free(file->file_path);
    free(file->file_extension);

}
/**
 * Duplicates the file information
 * ** Remember to destroy copy
 * @param src
 * @param dest
 */
static void fi_file_copy(const FiFileInfo_st *src, FiFileInfo_st *dest)
{
    if (! src || ! dest)
        return;

    dest->filename       = fi_strndup(src->filename, strlen(src->filename));
    dest->file_path      = fi_strndup(src->file_path, strlen(src->file_path));
    dest->file_extension = fi_strndup(src->file_extension, strlen(src->file_extension));
    dest->size_byte      = src->size_byte;
    dest->modified_at    = src->modified_at;
}

/**
 * Initializes the file array
 * @param array
 */
void fi_file_array_init(struct FiFileArray * array)
{
    if (! array)
        return;

    fi_array_init(&array->bank);
}

/**
 * @param arr
 * @param info
 * @return 
 */
int fi_file_array_add_file_info(struct FiFileArray *arr,
                                struct FiFileInfo *info)
{
    if (! info || ! arr)
        return -1;
    
    return 0;
}