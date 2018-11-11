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
#include "lib-common.h"

#include <stdlib.h>
#include <malloc.h>

#include "file.h"
#include "util-string.h"

const struct FiFileInfo EMPTY_FILE = {  
   {0, 0},              /* struct timespec */
   {0, NULL},           /* struct FiRef */
    NULL,               /* filename */
    NULL,               /* file_path */
    NULL,               /* full_filename */
    0L,                 /* size */
    0,                  /* file_type */
    false,              /* free_container */
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
    file->ref.free = fi_file_info_ref_destory;
    fi_ref_inc(&file->ref);
}

/**
 * Free the resources
 * @param file
 */
void fi_file_destroy(struct FiFileInfo * file)
{
    if (! file)
        return;

    fi_ref_dec(&file->ref);
}

static void fi_file_info_ref_destory(const struct FiRef *ref)
{
    struct FiFileInfo *file = container_of(ref, struct FiFileInfo, ref);

    if (NULL == file)
            return;

    fi_free(file->filename);
    fi_free(file->path);
    fi_free(file->full_filename);

    if (file->free_container)
        fi_free(file);
}

bool fi_file_copy_proxy(void const *src, void *dst, unsigned n)
{
    if (! src || ! dst)
        return false;
    
    if (n != sizeof(struct FiFileInfo)) {
        fi_log_message(FI_DEBUG_LEVEL_WARN,
            "Failed to copy data. Size mismatch. Expected %zu, got %d",
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

    fi_file_set_props(dest,
            src->filename,
            src->path,
            src->type,
            src->size_byte,
            src->modified_at,
            src->ref.free);

    return true;
}

char *fi_file_get_extension(struct FiFileInfo *file)
{
        char *h = strrchr(file->filename, '.');

        // Move one past the '.'
        return h ? (h + 1) : h;
}

void fi_file_set_props(struct FiFileInfo *file,
                       const char *filename,
                       const char *path,
                       unsigned int type,
                       off_t size,
                       struct timespec modified_at,
                       void (*free)(const struct FiRef *ref))
{
        file->filename = fi_strndup(filename, fi_strlen(filename));
        file->path = fi_strndup(path, fi_strlen(path));
        file->full_filename = fi_strconcat(
                       2,
                       path,
                       fi_strndup(file->filename, fi_strlen(file->filename)));
        file->type = type;
        file->size_byte = size;
        file->modified_at = modified_at;
        file->ref.free = free;
        file->ref.count = 0;
        fi_ref_inc(&file->ref);
}