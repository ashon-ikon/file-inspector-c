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
#include <bits/string2.h>

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
                            
extern const FiFileInfo EmptyInfo;

static char *
fi_detector_full_filename_m(const char *path, const char *filename)
{
    char *full_filename = fi_sstrdup("%s%c%s",path, path_separator, filename);;
    if (NULL == full_filename) {
        fi_print_error("Failed to allocate memory for full filename path");
        return NULL;
    }

    return full_filename;
}

static FiFileList *
fi_file_list_read_mirror_dir_content(FiFileList* list,
                                     const char * src,
                                     bool recursive)
{
    DIR* dir;
    struct dirent *dp;
    dir = opendir(src);

    while ((dp = readdir(dir)) != NULL && dp->d_name != NULL) {
        if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
            FiFileInfo *p_info = fi_file_list_get_file_info_from_dirent_m(src, dp);
            fi_file_list_add(list, p_info);
            
            if (recursive && p_info->file_type == FI_FILE_TYPE_DIRECTORY) {
                // Add directory content recursively
                char * full_filename = fi_detector_full_filename_m(src, dp->d_name);
                fi_file_list_read_mirror_dir_content(list, full_filename, recursive);
                free (full_filename);
                
            }
            fi_file_info_free(p_info);
        }
    }
    closedir(dir);

    return list;
}

void
fi_file_list_set_file_params (FiFileInfo *pinfo,
                              const char *filename)
{
    FiFileType t     = FI_FILE_TYPE_UNKNOWN;

    if (filename) {
        // Make the full path
        // Now let's attempt to the type via stat
        struct stat sb;
        if (lstat(filename, &sb) != -1) {
            switch (sb.st_mode & S_IFMT) {
                case S_IFREG: t = FI_FILE_TYPE_REGULAR;
                    break;
                case S_IFDIR: t = FI_FILE_TYPE_DIRECTORY;
                    break;
                case S_IFLNK: t = FI_FILE_TYPE_LINK;
                    break;
                case S_IFCHR:  /* Done intentionally */
                case S_IFIFO:
                case S_IFBLK:
                case S_IFSOCK:
                default:        /* Done intentionally */
                    t = FI_FILE_TYPE_UNKNOWN;
                    break;
            }
            // Set the size
            pinfo->size_byte = sb.st_size;
            // Set the modification times
            pinfo->modified_at  = sb.st_mtim;
        }
    }
    pinfo->file_type = t;
}

/**
 * Returns the FileInfo
 * @param dp
 * @return
 */
FiFileInfo *
fi_file_list_get_file_info_from_dirent_m(const char	     *path,
                             		 const struct dirent *dp)
{
    FiFileInfo * pinfo = malloc (sizeof (* pinfo));
    if (NULL == pinfo){
        fi_print_error("Failed to allocate enough memory. dirent");
        return NULL;
    }
    
    // Prefill the structure
    *pinfo = EmptyInfo;

    pinfo->filename     = strndup (dp->d_name, strlen(dp->d_name));
    pinfo->file_path    = strndup (path, strlen(path));
    if (DT_DIR != dp->d_type) {
        // Attempt to get the file extension
        char *ext_str = strrchr(dp->d_name, '.');
        char *f_name  = fi_detector_full_filename_m(path, dp->d_name);
        // Set the extension
        pinfo->file_extension = fi_strdup(! ext_str ? "UNKNONWN" : (ext_str + 1));
        fi_file_list_set_file_params (pinfo, f_name);
        free (f_name); // Release the dynamic filename buffer created

    } else {
        pinfo->file_extension   = strdup ("Dir");
        pinfo->file_type        = FI_FILE_TYPE_DIRECTORY;
    }

    return pinfo;
}


/**
 * Returns a pre-populated FileList structure
 * @param src
 * @param recursive
 * @return 
 */
FiFileList *
fi_file_list_get_list_from_source_m(const char * src, bool recursive)
{
    if (! strlen(src))  {
        fi_print_error("Failed to allocate enough new memory");
        return NULL;
    }
    
    FiFileList* list = fi_file_list_new();

    if (NULL != list) {
        fi_file_list_read_mirror_dir_content(list, src, recursive);
    }

    return list;
}
