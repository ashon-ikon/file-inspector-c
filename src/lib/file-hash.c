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
#include <stdio.h>

#include "file-hash.h"
#include "util-string.h" // Include <string.h>

size_t fi_hash_data (const void *data, size_t len)
{
    size_t hash, i;
    for(hash = i = 0; (*((char *)(data + i)) != '\0') && i < len; ++i)
    {
        hash += *((unsigned char*)(data + i));
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

size_t fi_file_get_content_hash(struct FiFileInfo *file)
{
        if (!file)
                return 0;
        
//        FILE *fp = fopen()
        return 0;
}

/**
 * We combine the filename and extension to create a hash
 * @param file
 * @return 
 */
size_t fi_file_get_hash(struct FiFileInfo *file)
{
        // Overflow is gracefully acceptable
        size_t v = fi_hash_data(file->filename, fi_strlen(file->filename));
//        v += fi_hash_data(file->extension, fi_strlen(file->extension));
        v += file->type;

        return v;
}