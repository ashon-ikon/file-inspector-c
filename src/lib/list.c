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

struct FiList *fi_list_new(void *data,
                           bool (*fn)(struct FiList * n))
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
    list->destroy_callback = fn ? fn : NULL;
    
    return list;
}

#include <stdio.h>
void fi_list_free(struct FiList *list)
{
    if (! list)
        return;

    // Traverse through the chain and free resources
    struct FiList *tail = fi_list_tail(list);
    struct FiList *prev  = fi_list_prev(tail);

    do {
        if (tail && tail->destroy_callback)
            tail->destroy_callback(tail);

        prev = fi_list_prev(tail);
        free(tail);

    } while (tail = prev);
}

void fi_list_append(struct FiList *list, struct FiList *next)
{
    if (! list || ! next)
        return;
    
    struct FiList *tail = fi_list_tail(list);
    tail->next = next;
    next->prev = tail;
}

void fi_list_prepend(struct FiList *list, struct FiList *prev)
{
    if (! list || ! prev)
        return;
    
    struct FiList *head = fi_list_head(list);
    head->prev = prev;
    prev->next = head;
}

unsigned fi_list_count(struct FiList *list)
{
    struct FiList *cur = fi_list_head(list);

    unsigned c = 0;

    if (cur)
        do
            c++;
        while(cur = cur->next);

    return c;
}

// Traversing
struct FiList *fi_list_head(struct FiList *list)
{
    if (! list)
        return NULL;

    struct FiList *cur = list;
    
    for (; cur->prev; cur = cur->prev);

    return cur;
}

struct FiList *fi_list_tail(struct FiList *list)
{
    if (! list)
        return NULL;

    struct FiList *cur = list;
    
    for (; cur && cur->next; cur = cur->next);

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

    for (; cur; cur = fi_list_next(cur))
        list_func(cur->data);
}
