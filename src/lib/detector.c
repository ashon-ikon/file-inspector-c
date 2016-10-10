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

#include <dirent.h>
#include <stdbool.h>
#include <stddef.h>         // defines NULL
#include <stdlib.h>         // malloc
#include <stdio.h>
#include <stdarg.h>         // vargs
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "debug.h"
#include "detector-private.h"
#include "file-list-array.h"
#include "string-helper.h"


const char path_separator =
#ifdef _WIN32
                            '\\';
#else
                            '/';
#endif


FiFileType
fi_get_file_type(const unsigned char *type, const char* path, const char* filename)
{
    FiFileType t = FI_FILE_TYPE_UNKNOWN;
    struct stat sb;
    size_t path_len = strlen(path),
            fname_len = strlen(filename);
    char *f_name;
    
    // First we'll attempt using regular dirent.d_type
    switch (*type) {
        case DT_DIR: t = FI_FILE_TYPE_DIRECTORY;
            break;
        case DT_REG: t = FI_FILE_TYPE_REGULAR;
            break;
        case DT_BLK:
        case DT_CHR: /* Done intentionally */
        case DT_FIFO:
        case DT_LNK:
        case DT_SOCK:
        case DT_UNKNOWN: /* Done intentionally */
        default:
            f_name = malloc(path_len + 1 + fname_len + 1); // path + P_Sep + filename + '\0'
            if (f_name) {
                // Make the full path
                strncpy(f_name, path, path_len);
                strncat(f_name, &path_separator, 1); // Add separator
                strncat(f_name, filename, fname_len); // Add filename
                // Now let's attempt to the type via stat
                if (stat(f_name, &sb) != -1) {
                    switch (sb.st_mode & S_IFMT) {
                        case S_IFREG: t = FI_FILE_TYPE_REGULAR;
                            break;
                        case S_IFDIR: t = FI_FILE_TYPE_DIRECTORY;
                            break;
                        case S_IFLNK: t = FI_FILE_TYPE_LINK;
                            break;
                        case S_IFCHR: /* Done intentionally */
                        case S_IFIFO:
                        case S_IFBLK:
                        case S_IFSOCK:
                        default: /* Done intentionally */
                            break;
                    }
                }
                if (f_name)
                    free(f_name); // Release the memory
                t = FI_FILE_TYPE_UNKNOWN;
            }
            break;
    }
    return t;
}

/**
 * Returns the FileInfo
 * @param dp
 * @return 
 */
FiFileInfo *
fi_get_file_info_from_dirent_m(const char           *path,
                             const struct dirent *dp)
{
    FiFileInfo * pinfo = malloc (sizeof (* pinfo));
    if (NULL == pinfo){
        fi_print_error("Failed to allocate enough memory. dirent");
        return NULL;
    }

    pinfo->filename     = strndup (dp->d_name, strlen(dp->d_name));
    pinfo->file_path    = strdup (path);
    unsigned char d_type = DT_UNKNOWN;
    pinfo->file_type    = fi_get_file_type(&d_type, path, dp->d_name);
//    pinfo->file_type    = fi_get_file_type(&dp->d_type, path, dp->d_name);
    // Attempt to get the file extension
    char* ext_str = strrchr(dp->d_name, '.');
    pinfo->file_extension = fi_strdup(! ext_str ? "UNKNONWN" : (ext_str + 1));
    
    return pinfo;
}


/**
 * Returns a pre-populated FileList structure
 * @param src
 * @return 
 */
FiFileList *
fi_get_file_list_from_source_m(const char * src)
{
    if (! strlen(src))  {
        fi_print_error("Failed to allocate enough new memory");
        return NULL;
    }
    
    DIR* dir;
    struct dirent *dp;
    dir = opendir(src);
    FiFileList* list = fi_file_list_new();

    while ((dp = readdir(dir)) != NULL && dp->d_name != NULL) {
        if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
            FiFileInfo *p_info = fi_get_file_info_from_dirent_m(src, dp);
            fi_file_list_add(list, p_info);
            fi_file_info_free(p_info);
        }
    }
    closedir(dir);
    
    return list;
}