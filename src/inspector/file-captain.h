/* 
 * File:   FileCaptain.h
 * Author: yasonibare
 * 
 * Copyright (c) 2016 Yinka Asonibare
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
 * Created on 28 August 2016, 10:42 PM
 */

#ifndef FINSPECTOR_FILE_CAPTAIN_H__
#define FINSPECTOR_FILE_CAPTAIN_H__

#include <algorithm>
#include <ctime>
#include <glibmm/ustring.h>
#include <functional>
#include <vector>
#include <map>


using Glib::ustring;

namespace FInspector {


/**
 * Types of File
 */
enum FileType {
    NO_USE,
    REGULAR_FILE,
    DIRECTORY,
    SYM_LINK,
    OTHER,
    TYPES_COUNT
};
    
/**
 * 
 */
class FileCaptain {
public:
    FileCaptain();
    FileCaptain(const FileCaptain& orig);
    
    bool checkSourceFolder(const ustring&);
    bool checkDestFolder(const ustring&);
    bool isDirectory(const ustring&);
    bool isFile(const ustring&);
    
    struct Fileinfo {
        Glib::ustring filename;
        Glib::ustring path;
        Glib::ustring re;
        time_t lastModifed;
        uintmax_t size;
        FileType type;

        bool operator<(const Fileinfo& rhs);
    };
    
    virtual ~FileCaptain();
private:

};

}

#endif /* FINSPECTOR_FILE_CAPTAIN_H__ */

