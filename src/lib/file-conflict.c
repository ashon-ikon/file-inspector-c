/* 
 * File:   file-conflict.c
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
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "file-conflict.h"
#include "debug.h"
#include "util-string.h"

static bool fi_conflict_group_free_cb(struct FiList *file);
static void free_conflict_group_ref(const struct FiRef *ref);


struct FiConfGroup *fi_conflict_group_new()
{
    struct FiConfGroup *grp = calloc(1, sizeof *grp);
    if (! grp) {
        fi_log_message(FI_DEBUG_LEVEL_ERROR,
                      "Failed to create conflict group list");
        return NULL;
    }
    
    grp->files = NULL;
    grp->common_container = false;
    grp->ref.count = 1;
    grp->ref.free  = free_conflict_group_ref;

    return grp;
}

static void free_conflict_group_ref(const struct FiRef *ref)
{
    struct FiConfGroup *grp = container_of(ref, struct FiConfGroup, ref);
    if (! grp)
        return;
    
    // Free the list
    fi_list_free(grp->files);
    
    if (! grp->common_container)
        free(grp);
}

void fi_conflict_group_free(struct FiConfGroup *grp)
{

    if (! grp)
        return;
    
    fi_ref_dec(&grp->ref);
}

static bool fi_conflict_group_free_cb(struct FiList *node)
{
    struct FiFileInfo *info = fi_list_data_ptr(node, struct FiFileInfo);
    fi_ref_dec(&info->ref_count);
}

void fi_conflict_group_add(struct FiConfGroup *self, struct FiFileInfo *file)
{
    if (! self || ! file)
        return;
        
    fi_ref_inc(&file->ref_count);

    struct FiList *list = fi_list_new(file, fi_conflict_group_free_cb);

    if (! fi_list_count(self->files))
        self->files = list;
    else 
        fi_list_append(self->files, list);

}

bool fi_conflict_group_has(struct FiConfGroup *self, struct FiFileInfo *file)
{

    if (! self || ! file)
        return false;

    struct FiList *c = NULL;

    for (c = self->files; c->prev; c = c->prev); // Move to head

    for (; c; c = c->next) {
        if ((struct FiFileInfo *)fi_list_data_ptr(c, struct FiFileInfo) == file)
            return true;
    }

    return false;
}

/// Conflict group cast macro
#define CONF_GRP(c) ((struct FiConfGroup *)(c))
/**
 * Copies struct FiConGroup.
 * 
 * Used by FiArray or any other quick copying of FiConfGroup
 * 
 * @param src
 * @param dst
 * @param n
 * @return 
 */
bool fi_conflict_group_copy(void const *src, void *dst, unsigned n)
{
    if (! src || ! dst)
        return false;


    
    struct FiList *head = NULL;
    // Rewind to beginning
    for(head = CONF_GRP(src)->files; head->prev; head = head->prev);

    for(struct FiList *cur = head; cur; cur = cur->next) {

        // create new file
        struct FiFileInfo *file = malloc(sizeof *file);
        if (file) {
            fi_file_init(file);
            file->free_container = true; // Memory should be freed on deallocation
            // copy the file
            fi_file_copy(fi_list_data_ptr(cur, struct FiFileInfo), file);
            // Add file to new group
            fi_conflict_group_add(CONF_GRP(dst), file);
            fi_ref_dec(&file->ref_count); // Free resources
        }

    }

    CONF_GRP(dst)->conflict_type_id = CONF_GRP(src)->conflict_type_id;
    CONF_GRP(dst)->ref.free         = CONF_GRP(src)->ref.free;
    fi_ref_inc( &(CONF_GRP(dst)->ref) );
    
}

// ------------------------------------------
// Conflict Group Array
// ------------------------------------------
void fi_conflict_array_init(struct FiConflictArray *arr)
{
    if (! arr)
        return;
    
    arr->file_groups = fi_array_new(sizeof *(arr->file_groups),
                                    fi_conflict_group_copy);
}

void fi_conflict_array_free(struct FiConflictArray *arr)
{
    if (! arr || ! arr->file_groups)
        return;

    struct FiConfGroup *grp;
    
    while(grp = fi_array_pop(arr->file_groups, struct FiConfGroup)) {
        fi_ref_dec(&grp->ref);  
    }
    
    fi_array_free(arr->file_groups);
}

void fi_conflict_array_add_group(struct FiConflictArray *arr,
                                 struct FiConfGroup *grp)
{
    if (! arr || ! grp)
        return;

    fi_array_push(arr->file_groups, grp);
    struct FiConfGroup *last = fi_array_get_ptr_end(arr->file_groups,
                                                    struct FiConfGroup);
    // We are going to be self-managing the destruction of the container
    last->common_container = true;

}
