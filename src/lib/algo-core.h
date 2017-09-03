/* 
 * File:   algo-core.h
 * Author: yasonibare
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

#ifndef FINSPECTOR_LIB_ALGO_CORE_H
#define FINSPECTOR_LIB_ALGO_CORE_H

#include <stdbool.h>

#include "array.h"
#include "lib-common.h"
#include "file-container.h"
#include "list.h"
#include "file-conflict.h"

FI_BEGIN_DECLS

#ifndef FI_MAX_NAME
#define FI_MAX_NAME        64
#define FI_MAX_DESC        512
#endif

struct FiAlgo {
    char            name[FI_MAX_NAME];
    char            desc[FI_MAX_DESC];
    unsigned        conflict_type_id;

    /* Extracts an array of FiConfGroups */
    struct FiConflictArray *(*extract_conflicts) (struct FiAlgo *self,
                                         struct FiFileContainer *all_files);
};

/*
 * 
 *  This will help visualize the relationship between the structures
 * 
 *  The basic conflict grouping is as such:
 *  algo_1
 *     |
 *     |   (FiConflictArray)
 *     |
 *     |_____ Group1 (FiConfGroup)
 *     |     |___ files (FiList)
 *     |     |     |___ file1 (FiConfFile / FiFileInfo)
 *     |     |     |___ file2
 *     |     |
 *     |     |___ conflict_type_id
 *     |
 *     |_____ Group2
 * 
 * 
 */

struct FiAlgoCollection {
    struct FiList  *algos;
    struct FiConflictArray * (*get_conflicts)(void);
    struct FiConflictArray *conflicts;
};

void fi_algo_collection_init(struct FiAlgoCollection *coll);
void fi_algo_collection_free(struct FiAlgoCollection *coll);


FI_END_DECLS

#endif /* FINSPECTOR_LIB_ALGO_CORE_H */

