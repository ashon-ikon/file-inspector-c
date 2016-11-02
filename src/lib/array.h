/* 
 * File:   array.h
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

#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

#include "lib-common.h"

FI_BEGIN_DECLS

struct FiContainer_st {
    void        *container;
    unsigned     size;
    int          count;
    int         (*inc_ref) (struct FiContainer_st *con);
    int         (*dec_ref) (struct FiContainer_st *con);
};

struct FiArray_st {
    unsigned               len;
    unsigned               capacity;
    struct FiContainer_st *data;
};

void  fi_array_init(struct FiArray_st *arr);
void  fi_array_destroy(struct FiArray_st *arr);
short fi_array_push(struct FiArray_st *arr, void * data, unsigned n);
struct FiContainer_st *fi_array_get(struct FiArray_st *arr, struct FiContainer_st *dest, unsigned i);
void  fi_array_copy(const struct FiArray_st *src, struct FiArray_st *dst);

        
FI_END_DECLS

#endif /* ARRAY_H */

