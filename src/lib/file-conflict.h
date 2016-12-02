/* 
 * File:   file-conflict.h
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

#ifndef FINSPECTOR_LIB_FILE_CONFLICT_H
#define FINSPECTOR_LIB_FILE_CONFLICT_H

#include <stdbool.h>

#include "array.h"
#include "file.h"
#include "lib-common.h"
#include "list.h"

FI_BEGIN_DECLS

#ifndef FI_MAX_NAME
#define FI_MAX_NAME        64
#define FI_MAX_DESC        512
#endif


/**
 * File Conflict Group
 *
 * This is holds a list of files in conflict based on algorithm's rules.
 * Each of this conflict groups will be sorted, hopefully by the detector
 * later
 */

struct FiConfFile {
    struct FiFileInfo parent;
    unsigned char     mapped;
};

struct FiConfGroup {
    struct FiList *files; /* List of FiConfFile / FiFileInfo */
    unsigned       conflict_type_id;
};


struct FiConflictArray {
    struct FiArray *file_groups;
};

struct FiConfGroup *fi_conflict_group_new();
void fi_conflict_group_free(struct FiConfGroup *grp);
void fi_conflict_group_add(struct FiConfGroup *self, struct FiFileInfo *file);
bool fi_conflict_group_has(struct FiConfGroup *self, struct FiFileInfo *file);


FI_END_DECLS

#endif /* FINSPECTOR_LIB_FILE_CONFLICT_H */

