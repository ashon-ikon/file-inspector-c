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
#include "debug.h"

/* This is the minimum items in list to start with 
 */
#define FI_ARRAY_ALLOC_CHUNK_SIZE 20

typedef struct FiContainer FiContainer_st;

static FiContainer_st empty_content = {NULL, 0, {0, NULL}};

/* Prototypes */
static bool fi_array_expand_container(struct FiArray **cur, unsigned n);
static void fi_array_container_create(struct FiContainer *con,
                                      void *data, FI_DATA_SIZE size);
static void fi_array_container_free(const struct FiRef *con);


/* Helper macros */


/**
 * Creates the array holder
 * @return 
 */
void fi_array_init(struct FiArray *arr)
{
    if (! arr) { 
        fprintf(stderr, "Failed to allocate memory for array\n");
        return;
    }
    
    arr->capacity  = 0;
    arr->len       = 0;
    arr->container = NULL;
    fi_array_expand_container(&arr, FI_ARRAY_ALLOC_CHUNK_SIZE);

    return;
}

void fi_array_destroy(struct FiArray *arr)
{
    if (arr) {
        for (unsigned i = 0; i < arr->capacity; i++)
            fi_ref_dec(&arr->container[i].reference);
        free(arr->container);
    }
}

/**
 * Expands the current array
 * @param cur
 * @param n
 * @return 
 */
static bool fi_array_expand_container(struct FiArray ** cur, unsigned n)
{
    struct FiContainer *tmp =
        realloc((*cur)->container, n * sizeof(*tmp));
    
    if (NULL != tmp) {

        // Empty out the container
        for (unsigned i = (*cur)->capacity; i < n; i++)
            // Assign the empty value
            tmp[i] = empty_content;

        (*cur)->container = tmp;
        (*cur)->capacity  = n;
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
short fi_array_push (struct FiArray *arr, void * data, FI_DATA_SIZE size)
{

    if (arr->capacity < (1 + arr->len))
        if (! fi_array_expand_container(&arr, arr->capacity * 2))
            return -1;
    
    fi_array_container_create(&arr->container[arr->len++], data, size);

    return 0;
}

/**
 * This attempts to return just the exact data that was stored
 * @param arr
 * @param i
 */
struct FiContainer *fi_array_get(struct FiArray *arr, u_int i)
{
    if (! arr)
        return NULL;

    struct FiContainer *dest;

    if (i >= 0 && i < arr->len) { 

        dest = &arr->container[i];
        fi_ref_inc(&dest->reference);

    } else {
        *dest = empty_content;
        fi_log_message(FI_DEBUG_LEVEL_WARN, "Subscript '%d' out of range\n", i);
    }

    return dest;
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

    dst->container = malloc(src->capacity * sizeof(dst->container[0]));
    if (dst->container) {

        for (unsigned i = 0; i < src->capacity; i++)
            fi_array_container_create(&dst->container[i],
                                      src->container[i].data,
                                      src->container[i].size);

        dst->len = src->len;
        dst->capacity = src->capacity;
    }
}


/**
 * Intializes container
 * @param data
 * @param size
 * @return 
 */
static void fi_array_container_create(struct FiContainer *p,
        void *data, FI_DATA_SIZE size)
{
    
    *p = empty_content;

    if (data) {
        p->data    = malloc((size_t)size);
        if (! p->data) {
            fi_log_message(FI_DEBUG_LEVEL_CRITICAL,
                           "Failed to allocate array container data memory");
            return;
        }
        memcpy(p->data, data, size);
        p->reference.free = fi_array_container_free;
        p->size           =  size;
        fi_ref_inc(&p->reference);
    }

}

static void fi_array_container_free(const struct FiRef *ref)
{
    if (! ref)
        return;
    struct FiContainer *con = container_of(ref, struct FiContainer, reference);
    
    if (! con)
        return;

    free(con->data);
}
