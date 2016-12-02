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

#include "file-conflict.h"
#include "debug.h"
#include "util-string.h"

static bool fi_config_group_free_cb(struct FiList *file);


struct FiConfGroup *fi_conflict_group_new()
{
    struct FiConfGroup *grp = calloc(1, sizeof *grp);
    if (! grp) {
        fi_log_message(FI_DEBUG_LEVEL_ERROR,
                      "Failed to create conflict group list");
        return NULL;
    }
    
    grp->files = NULL;

    return grp;
}

void fi_conflict_group_free(struct FiConfGroup *grp)
{
    if (! grp)
        return;

    // Free the list
    fi_list_free(grp->files);

    free(grp);
}

static bool fi_config_group_free_cb(struct FiList *node)
{
    fi_file_destroy(fi_list_data_ptr(node, struct FiFileInfo));
}

void fi_conflict_group_add(struct FiConfGroup *self, struct FiFileInfo *file)
{
    if (! self || ! file)
        return;

    if (! fi_list_count(self->files))
        self->files = fi_list_new(file, fi_config_group_free_cb);
    else 
        fi_list_append(self->files, fi_list_new(file, fi_config_group_free_cb));
}

bool fi_conflict_group_has(struct FiConfGroup *self, struct FiFileInfo *file)
{
    for (struct FiList *c = fi_list_head(self->files); c; c = c->next) {
        if ((struct FiFileInfo *)fi_list_data_ptr(c, struct FiList) == file)
            return true;
    }

    return false;
}