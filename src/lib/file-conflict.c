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
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "file-conflict.h"
#include "util-string.h"


struct FiConflictList *fi_conflict_new(const char *name)
{
    struct FiConflictList *list = malloc(sizeof *list);
    if (! list) {
        fi_log_message(FI_DEBUG_LEVEL_ERROR,
                      "Failed to create conflict list");
        return NULL;
    }
    list->con  = fi_file_container_init();
    strncpy(list->name, name, FI_MAX_NAME - 1);
    
    return list;
}

void fi_conflict_destroy(struct FiConflictList *list)
{
    if (! list)
        return;    

    fi_file_container_destroy(list->con);

    free(list);
      
}
