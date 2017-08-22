/*
 * File:   file-manager.c
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
#include <dirent.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>

#include "debug.h"
#include "file.h"
#include "file-manager.h"
#include "util-string.h"

const char path_separator =
#ifdef _WIN32
        '\\';
#else
        '/';
#endif

// Prototypes ...
static bool read_file_info(const char const *path,
                         const char const  *filename, struct FiFileInfo *file);
static char *file_extension(const char const *filename);
static FiFileType get_file_type(const mode_t d_type);

/**
 * Method responsible for reading contents of a directory
 * 
 * <code>
 *         struct FiFileContainer *files = fi_file_container_init();
 *         fi_file_manager_read_dir("/path/to/folder", files, false);
 *
 *         // ... do something with files
 *
 *         fi_file_container_destroy(files);
 * </code>
 * 
 * @param path
 * @param con
 * @param recursive
 * @return 
 */
bool fi_file_manager_read_dir(const char const       *path,
                              struct FiFileContainer *con,
                              bool                    recursive)
{
    if (! path || ! con)
        return false;

    DIR* dir;
    struct dirent *dp;
    
    if (! (dir = opendir(path))) {
        fi_log_message(FI_DEBUG_LEVEL_WARN,
                       "Could not read the specified path %s", path);
        return false;
    }
    
    struct FiFileInfo file;
    char path_sep[] = {path_separator, '\0'};
    
    while ((dp = readdir(dir)) != NULL) {
        
        if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")) {
            fi_file_init(&file);
            if (! read_file_info(path, dp->d_name, &file))
                continue;

            fi_file_container_push(con, &file);
            if (recursive && file.type == FI_FILE_TYPE_DIRECTORY) {
                // Add directory content recursively
                char *full_filename = fi_strconcat(3, path, path_sep, dp->d_name);
                fi_file_manager_read_dir(full_filename, con, recursive);
                free(full_filename);
            }
            fi_file_destroy(&file);
        }
    }
    closedir(dir);
    
    return true;
}

static bool read_file_info(const char const  *path,
                           const char const  *filename,
                           struct FiFileInfo *file)
{
    // Read the file information by lstat
    struct stat st_buff;
    char path_sep[] = {path_separator, '\0'};
    char *fullpath = fi_strconcat(3, path, path_sep, filename);
    if (! fullpath)
        return false;

    if (lstat(fullpath, &st_buff) == -1) {
        free (fullpath);
        return false;
    }
    free (fullpath);

    char *ext = file_extension(filename);
    
    file->extension   = fi_strdup(ext ? ext : "");
    file->path        = fi_strndup(path,     strlen(path));
    file->filename    = fi_strndup(filename, strlen(filename));
    file->size_byte   = st_buff.st_size;
    file->type        = get_file_type(st_buff.st_mode);
    file->modified_at = (struct timespec) st_buff.st_mtim;

    return true;
}

static FiFileType get_file_type(const mode_t st_mode)
{
    FiFileType ftype = FI_FILE_TYPE_UNKNOWN;

    switch (st_mode & S_IFMT) {
    case S_IFDIR:  ftype = FI_FILE_TYPE_DIRECTORY; break;
    case S_IFREG:  ftype = FI_FILE_TYPE_REGULAR; break;
    case S_IFLNK:  ftype = FI_FILE_TYPE_LINK; break;
    case S_IFBLK:  /* Left intentionally */
    case S_IFCHR:  /* Left intentionally */
    case S_IFIFO:  /* Left intentionally */
    case S_IFSOCK: /* Left intentionally */
    default:
        ftype = FI_FILE_TYPE_UNKNOWN;
        break;
    }
    
    return ftype;
}


static char *file_extension(const char const *filename)
{
    char *h = strrchr(filename, '.');
    
    // Move one past the '.'
    return h ? (h + 1) : h;
}

bool fi_file_manager_copy_file(const char const *filepath,
                               bool              remove_source)
{
    if (! filepath)
        return false;
    
    if (remove_source)
        ;
}