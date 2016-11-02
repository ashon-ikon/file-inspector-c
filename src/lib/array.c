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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

/* This is the minimum items in list to start with 
 */
#define FI_ARRAY_ALLOC_CHUNK_SIZE 20

typedef struct FiContainer_st FiContainer;

static FiContainer empty_content = {NULL, 0};

/* Prototypes */
static bool fi_array_expand_container(struct FiArray_st **cur, unsigned n);
static bool fi_array_copy_container(const FiContainer *src, FiContainer *dst);

/* Helper macros */

/**
 * Creates the array holder
 * @return 
 */
void fi_array_init(struct FiArray_st *arr)
{
    if (! arr) { 
        fprintf(stderr, "Failed to allocate memory for array\n");
        return;
    }
    
    arr->capacity = 0;
    arr->len      = 0;
    arr->data     = NULL;
    fi_array_expand_container(&arr, FI_ARRAY_ALLOC_CHUNK_SIZE);

    return;
}

void fi_array_destroy(struct FiArray_st *arr)
{
    if (arr) {
        for (unsigned i = 0; i < arr->capacity; i++)
            free(arr->data[i].container);
        free(arr->data);
    }
}

/**
 * Expands the current array
 * @param cur
 * @param n
 * @return 
 */
static bool fi_array_expand_container(struct FiArray_st ** cur, unsigned n)
{
    struct FiContainer_st *tmp =
        realloc((*cur)->data, (*cur)->capacity + n * sizeof(*tmp));
    
    if (NULL != tmp) {

        unsigned cap      = (*cur)->capacity;
        (*cur)->capacity += n;
        // Empty out the container
        for (unsigned i = cap; i < (*cur)->capacity; i++)
            // Assign the empty value
            tmp[i] = empty_content;

        (*cur)->data = tmp;
        return true;
    }
    
    return false;
}

/**
 * Adds data to array
 * @param arr
 * @param data
 * @param n
 */
short fi_array_push (struct FiArray_st *arr, void * data, unsigned n)
{
    unsigned n_size = n + arr->len;
    if (n_size >= arr->capacity) {
        if ( ! fi_array_expand_container(&arr,
                arr->capacity + FI_ARRAY_ALLOC_CHUNK_SIZE) )
            return -1;
    }

    unsigned i = arr->len++;
    arr->data[i].container = malloc(n);

    if (! arr->data[i].container) {
        fprintf(stderr, "Failed to allocate memory to store %d th element\n", i);
        return -1;
    }

    memcpy(arr->data[i].container, data, n);
    arr->data[i].size = n;
    
    return 0;
}

/**
 * This attempts to return just the exact data that was stored
 * @param arr
 * @param i
 */
struct FiContainer_st *fi_array_get(struct FiArray_st *arr,
                                    struct FiContainer_st *dest, u_int i)
{
    if (i >= 0 && i < arr->len) 
        *dest = arr->data[i];
    else {
        *dest = empty_content;
        fprintf(stderr, "Subscript '%d' out of range\n", i);
    }

    return dest;
}

/**
 * Duplicates an array
 * @param src
 * @param dst
 */
void  fi_array_copy(const struct FiArray_st *src, struct FiArray_st *dst)
{
    if (src->len) {

        dst->data = malloc(src->capacity * sizeof(dst->data[0]));
        if (dst->data) {

            for (unsigned i = 0; i < src->capacity; i++)
                fi_array_copy_container(&src->data[i], &dst->data[i]);

            dst->len = src->len;
            dst->capacity = src->capacity;
        }
    }
}

/**
 * Copies the container
 * @param src
 * @param dst
 * @return 
 */
static bool fi_array_copy_container(const FiContainer* src, FiContainer* dst)
{
    if (! src) {
        dst = NULL;
        return false;
    }

    dst->container = malloc(src->size);

    if (dst->container) {
        memcpy(dst->container, src->container, src->size);
        dst->count   = src->count;
        dst->dec_ref = src->dec_ref;
        dst->inc_ref = src->inc_ref;
        dst->size    = src->size;

        return true;
    }
    else
        return false;

}