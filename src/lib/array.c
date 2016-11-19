/*
 * File:   array.c
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

#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/X.h>

#include "array.h"
#include "debug.h"

/* This is the minimum items in list to start with 
 */
#define FI_INITIAL_ARRAY_ALLOC_SIZE 1 << 4

/* Prototypes */
static bool fi_array_expand_container(struct FiArray *cur, unsigned n);
static bool fi_array_data_copy(void const *src, void *dest, unsigned n);

/* Helper macros */
#define fi_data_get_offset(array, i) ((array)->data + (array)->unit_size * (i))


static FI_TYPE_SIZE fi_mem_best_size(FI_TYPE_SIZE desired, FI_TYPE_SIZE sz) {
    
    FI_TYPE_SIZE best =0, s = 0;
    s = desired > sz ? desired : sz;

    do 
        best = 1 << best;
    while (best < s);
    
    return best;
}

/**
 * Creates the array holder
 * @return struct FiArray *
 */
struct FiArray *fi_array_new(size_t unit_size, fi_array_data_cp_fn cp)
{
    struct FiArray *arr = malloc(sizeof *arr);
    if (! arr) {
        fi_log_message(FI_DEBUG_LEVEL_FATAL,
                       "Failed to allocate memory for array\n");
        return NULL;
    }

    arr->cleanup_notify = NULL;
    arr->data      = NULL;
    arr->unit_size = unit_size;
    arr->capacity  = 0;
    arr->len       = 0;
    arr->cursor    = -1;
    arr->ref_count = (struct FiRef){0, NULL};
    arr->copy_func = cp == NULL ? fi_array_data_copy : cp;
    fi_array_expand_container(arr, fi_mem_best_size(unit_size,
                              FI_INITIAL_ARRAY_ALLOC_SIZE));
    
    fi_ref_inc(&arr->ref_count);

    return arr;
}

void fi_array_destroy(struct FiArray *arr)
{
    if (arr) {
        if (arr->cleanup_notify)
            arr->cleanup_notify(arr);

        free(arr->data);
        free(arr);
    }
}

static bool fi_array_data_copy(void const *src, void* dest, unsigned n)
{
    if (src && dest) {
        memcpy(dest, src, n);
        return true;
    }

    return false;
}

/**
 * Expands the current array
 * @param cur
 * @param n
 * @return 
 */
static bool fi_array_expand_container(struct FiArray * cur, unsigned n)
{
    void *tmp = realloc(cur->data, n * cur->unit_size);
    
    if (NULL != tmp) {

        // Empty out the container
        memset(tmp + cur->capacity, 0, n);

        cur->data = tmp;
        cur->capacity  = n;
        return true;
    }
    
    return false;
}

/**
 * Adds data to array
 * @param arr
 * @param data
 */
short fi_array_push (struct FiArray *arr, void const *data)
{
    if (! arr)
        return FI_FUNC_FAIL;

    if ((arr->capacity < (1 + arr->len)) 
    && ! fi_array_expand_container(arr, fi_mem_best_size(1, arr->capacity * 2)))
            return FI_FUNC_FAIL;

    return fi_array_insert(arr, data, arr->len++);

}


short fi_array_insert(struct FiArray *arr, void const *data, FI_TYPE_SIZE i)
{
    if (! data || ! arr)
        return FI_FUNC_FAIL;
    
    if (i < 0 || i >= arr->capacity)
        return FI_FUNC_FAIL;
    
    memcpy(fi_data_get_offset(arr, i), data, arr->unit_size);

    // Set the cursor
    arr->cursor = i;

    return FI_FUNC_SUCCEED;    
}

/**
 * Duplicates an array
 * @param src
 * @param dst
 */
void  fi_array_copy(const struct FiArray *src, struct FiArray *dst)
{
    if (! src->len)
        return;

    for (FI_TYPE_SIZE i = 0; i < src->capacity; i++)
        fi_array_insert(dst, fi_array_get_ptr(src, void, i), i);

    dst->len = src->len;
    dst->capacity = src->capacity;
}


void *_fi_array_get_begin(struct FiArray *arr)
{
    if (! arr || arr->cursor < 0 || arr->len == 0)
        return NULL;
    
    arr->cursor = 0;
    
    return fi_array_get_ptr(arr, void *, arr->cursor);
}

/**
 * Returns the next available data. NULL if cursor is out of scope
 * 
 * @param arr
 * @return 
 */
void *_fi_array_get_next(struct FiArray *arr)
{
    if (! arr || arr->cursor < 0)
        return NULL;
    
    arr->cursor++;
    
    if (arr->cursor >= arr->len) {
        arr->cursor = arr->len;
        return NULL;
    }
    
    return fi_array_get_ptr(arr, void *, arr->cursor);
}

void *_if_array_get_end(struct FiArray *arr)
{
    if (! arr || arr->cursor < 0 || arr->len == 0)
        return NULL;
    
    arr->cursor = arr->len - 1;
    
    return fi_array_get_ptr(arr, void *, arr->cursor);
}