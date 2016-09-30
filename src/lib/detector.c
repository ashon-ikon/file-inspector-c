/**
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
 * 
 */

#include <stdbool.h>
#include <stddef.h>         // defines NULL
#include <stdlib.h>         // malloc
#include "detector-private.h"

/* This is the minimum items in list to start with 
 */
#define MIN_FILE_LIST_ALLOC 20

/**
 * Returns an empty
 * @return FiFileList
 */
static FiFileList *
fi_file_list_new ()
{
    FiFileList * list;

    // Initialize stuct
    list->pfile_info_list = 
            (FiFileInfo **) malloc(sizeof (FiFileInfo) * MIN_FILE_LIST_ALLOC);
    
    if (NULL == list->pfile_info_list) 
        return NULL;
    
    list->length = 0;
    list->capacity = MIN_FILE_LIST_ALLOC;

    return list;
}

static FiFileList *
fi_file_list_add (FiFileList * self, FiFileInfo * file_info)
{
    FiFileInfo ** pfile_info_list;
    FiFileList * tmp;
    
    // Scale up size if required
    if ((self->length + 1) > self->capacity)
        tmp->pfile_info_list = 
                (FiFileInfo **) realloc(self->pfile_info_list,
                                        self->capacity + MIN_FILE_LIST_ALLOC);
}

static bool
fi_file_list_free (FiFileList * self)
{

}
