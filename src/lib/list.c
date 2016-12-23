/*
 * File:   list.c
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

#include <stdlib.h>

#include "list.h"
#include "debug.h"

static void fi_list_ref_callback(const struct FiRef *ref);
static struct FiList *_fi_list_head(struct FiList *list);
static struct FiList *_fi_list_tail(struct FiList *list);

struct FiList *fi_list_new(void  *data,
                           bool (*destroy)(struct FiList * n))
{
    struct FiList *list = malloc(sizeof *list);
    if (! list) {
        fi_log_message(FI_DEBUG_LEVEL_ERROR,
                      "Failed to create new list");
        return NULL;
    }
    
    list->prev = NULL;
    list->next = NULL;
    list->data = data ? data : NULL;
    list->ref.count = 1;
    list->ref.free  = fi_list_ref_callback;
    list->destroy_callback = destroy ? destroy : NULL;
    
    return list;
}

void fi_list_free(struct FiList *list)
{
    if (! list)
        return;

    list = _fi_list_tail(list); // Move to the tail
    fi_ref_dec(&list->ref);
}

#include <stdio.h>
static void fi_list_ref_callback(const struct FiRef *ref)
{
    struct FiList *list = container_of(ref, struct FiList, ref);

    if (! list)
        return;

    // Traverse through the chain and free resources
    struct FiList *prev = list->prev;

    if (list->destroy_callback)
        list->destroy_callback(list);

    free(list);

    if (prev) {
        prev->next = NULL;
        fi_ref_dec(&prev->ref);
    }

}

void fi_list_append(struct FiList *list, struct FiList *next)
{
 
    if (! next)
        return;

    if (! list) {
        list = next; // Make this the first
        list->next = NULL;
        return;
    }

    struct FiList *tail = _fi_list_tail(list);
    tail->next = next;
    next->prev = tail;
}

void fi_list_prepend(struct FiList *list, struct FiList *prev)
{

    if (! prev)
        return;

    if (! list) {
        list = prev; // Make this the first
        list->prev = NULL;
        return;
    }
    
    struct FiList *head = _fi_list_head(list);
    head->prev = prev;
    prev->next = head;
}

unsigned fi_list_count(struct FiList *list)
{

    unsigned c = 0;

    if (list) {
        struct FiList *cur = _fi_list_head(list);
        do
            c++;
        while(cur = cur->next);
    }

    return c;
}

// Traversing
struct FiList *fi_list_head(struct FiList *list)
{
    if (! list)
        return NULL;

    struct FiList *cur = _fi_list_head(list);

    fi_ref_inc(&cur->ref);

    return cur;
}

struct FiList *fi_list_tail(struct FiList *list)
{
    if (! list)
        return NULL;

    struct FiList *cur = _fi_list_tail(list);

    fi_ref_inc(&cur->ref);

    return cur;
}

struct FiList *_fi_list_head(struct FiList *list)
{
    struct FiList *cur = list;
    
    for (; cur->prev; cur = cur->prev);

    return cur;
}

struct FiList *_fi_list_tail(struct FiList *list)
{
    struct FiList *cur = list;
    
    while (cur->next) {
        cur = cur->next;
    }

    return cur;
}

/**
 * Calls the callback function passing the data from the list node per time
 * @param list
 * @param list_func
 */
void fi_list_each(struct FiList *list, void (*list_func) (void *data))
{
    struct FiList *cur = fi_list_head(list);
    
    if (! cur || ! list_func)
        return;

    struct FiList *last = NULL;
    while(cur) {
        list_func(cur->data);
        last = cur;
        cur = fi_list_next(cur); // Advance it
        fi_ref_dec(&last->ref); // Free last
    }
}
