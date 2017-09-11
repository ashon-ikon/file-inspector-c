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

#ifndef FINSPECTOR_ARRAY_H
#define FINSPECTOR_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

#include "lib-common.h"
#include "ref.h"

FI_BEGIN_DECLS

#define FI_TYPE_SIZE    long unsigned int


struct FiArray;

typedef bool (*fi_array_data_cp_fn) (void const *src, void *dst, unsigned n);

struct FiArray {
    void          *data;
    FI_TYPE_SIZE   len;
    FI_TYPE_SIZE   capacity;
    size_t         unit_size;
    FI_TYPE_SIZE   cursor;
    struct FiRef   ref_count;
    void         (*cleanup_notify)(struct FiArray* arr);
    fi_array_data_cp_fn copy_func;
};

struct FiArray *fi_array_new_n(size_t unit_size,
                               fi_array_data_cp_fn cp,
                               FI_TYPE_SIZE n);
struct FiArray *fi_array_new(size_t unit_size, fi_array_data_cp_fn cp);
void  fi_array_free(struct FiArray *arr);
void  fi_array_ref_dec(const struct FiRef *ref);
void  fi_array_destroy(struct FiArray *arr);
void  fi_array_copy(const struct FiArray *src, struct FiArray *dst);
short fi_array_push(struct FiArray *arr, void const *data);
void *_fi_array_pop(struct FiArray *arr);
short fi_array_insert(struct FiArray *arr, void const *data, FI_TYPE_SIZE i);
void fi_array_set_cleanup_notifier(struct FiArray *arr, 
                                   void  (*fn)(struct FiArray *));

void *_fi_array_get_begin(struct FiArray *arr);
void *_fi_array_get_next(struct FiArray *arr);
void *_fi_array_get_prev(struct FiArray *arr);
void *_fi_array_get_end(struct FiArray *arr);

#define fi_array_pop(arr, t)    ((t *)_fi_array_pop((arr)))
#define fi_array_get_ptr(a, t, i) ((t*)( (a)->data + ( (a)->unit_size * (i) )) )
#define fi_array_get(a, t, i) ( ((t*)(void *)(a)->data) [(i)] )

#define fi_array_get_ptr_being(a, t)    ( (t*) _fi_array_get_begin((a)) )
#define fi_array_get_ptr_next(a, t)     ( (t*) _fi_array_get_next((a)) )
#define fi_array_get_ptr_prev(a, t)     ( (t*) _fi_array_get_prev((a)) )
#define fi_array_get_ptr_end(a, t)      ( (t*) _fi_array_get_end((a)) )


#define fi_array_each(a, t, pd) for ((pd) = (t*) _fi_array_get_begin((a)); \
                                     (pd) ; \
                                     (pd) = (t*) _fi_array_get_next((a)) )

static inline FI_TYPE_SIZE fi_array_size(struct FiArray *arr)
{
    return arr->len;
}

static inline FI_TYPE_SIZE fi_array_capacity(struct FiArray *arr)
{
    return arr->capacity;
}

        
FI_END_DECLS

#endif /* FINSPECTOR_ARRAY_H */

