/*
 * File:   list.h
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

#ifndef FINSPECTOR_LIB_LIST_H
#define FINSPECTOR_LIB_LIST_H

#include <stdbool.h>

#include "lib-common.h"
#include "ref.h"

FI_BEGIN_DECLS
        
        
struct FiList {
    struct FiList *prev;
    struct FiList *next;
    struct FiRef   ref;
    void          *data;
    bool (*destroy_callback)(struct FiList *node);
};

// Data Access
#define fi_list_data_ptr(n, t)      ((t*)(void *) (n)->data)

struct FiList *fi_list_new(void  *data,
                           bool (*destroy)(struct FiList * n));
void fi_list_free(struct FiList *list);
void fi_list_append(struct FiList *list, struct FiList *next);
void fi_list_prepend(struct FiList *list, struct FiList *prev);
unsigned fi_list_count(struct FiList *list);

// Traversing
struct FiList *fi_list_head(struct FiList *list);
struct FiList *fi_list_tail(struct FiList *list);

static inline struct FiList *fi_list_prev(const struct FiList const *list)
{
    return (list && list->prev) ? list->prev : NULL;
}

static inline struct FiList *fi_list_next(const struct FiList const *list)
{
    return (list && list->next) ? list->next : NULL;    
}
void fi_list_each(struct FiList *list, void (*list_func)(void *data));

FI_END_DECLS

#endif /* FINSPECTOR_LIB_LIST_H */

