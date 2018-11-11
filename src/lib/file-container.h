/*
 * File:   file-container.h
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

#ifndef FINSPECTOR_FILE_CONTAINER_H__
#define FINSPECTOR_FILE_CONTAINER_H__

#ifdef __cplusplus
extern "C" {
#endif
    
#include "file.h"


struct FiFileContainer {
    /**
     * All file information will be stored in this array object
     * to allow for easy access / traversing
     */
    struct FiArray *array;
};



// File array
struct FiFileContainer *fi_file_container_init();
void fi_file_container_destroy(struct FiFileContainer *container);
unsigned short fi_file_container_push(struct FiFileContainer *arr,
                                      struct FiFileInfo  *info);

static inline size_t fi_file_container_size(struct FiFileContainer *con)
{
    if (!con)
        return 0;

    return con->array->len;
}

struct FiFileInfo *fi_file_container_get_file_at(struct FiFileContainer *arr, unsigned long i);
struct FiFileInfo *fi_file_container_get_file_begin(struct FiFileContainer *con);
struct FiFileInfo *fi_file_container_get_file_next(struct FiFileContainer *con);
struct FiFileInfo *fi_file_container_get_file_end(struct FiFileContainer *con);

/*
 * Custom iterator for files within a container
 * NOTE: To avoid leakage always destroy pFile fi_ref_dec(pFile)
 */
#define fi_file_container_each(pCon, pFile) for ( \
                (pFile) = fi_file_container_get_file_begin((pCon)); \
                (pFile); \
                (pFile) = fi_file_container_get_file_next((pCon)) ) 




#ifdef __cplusplus
}
#endif

#endif /* FINSPECTOR_FILE_CONTAINER_H__ */

