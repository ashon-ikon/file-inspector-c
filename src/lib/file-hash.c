/* 
 * File:   file-hash.c
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
#include <stdint.h>
#include <stdlib.h>

#include "file-hash.h"
#include "util-string.h" // Include <string.h>

static uint32_t
fi_hash_string (const char *key, size_t len)
{
    uint32_t hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/*
 
struct FiFileInfo {
    char               *filename;
    char               *path;
    char               *extension;
    off_t               size_byte;
    bool                free_container;
    FiFileType          type;
    struct timespec     modified_at;
    struct FiRef        ref;
};*/

/**
 * We combine the filename and extension to create a hash
 * @param file
 * @return 
 */
size_t fi_file_get_hash(struct FiFileInfo *file)
{
        // Overflow is gracefully acceptable
        size_t v = fi_hash_string(file->filename, fi_strlen(file->filename));
        v += fi_hash_string(file->extension, fi_strlen(file->extension));

        return v;
}