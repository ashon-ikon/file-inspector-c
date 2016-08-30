/* 
 * File:   FileCaptain.cc
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

#include <iostream>

#include "file-captain.h"

namespace FInspector {

    FileCaptain::FileCaptain() {
    }

    FileCaptain::FileCaptain(const FileCaptain& orig) {
    }

    FileCaptain::~FileCaptain() {
    }

    /**
     * 
     * @param path
     * @return 
     */
    bool
    FileCaptain::checkSourceFolder(const ustring& path) {
        if (path.empty()) {

        }
        std::cout << path.length() << std::endl;
        return true;
    }

    /**
     * 
     * @param path
     * @return 
     */
    bool
    FileCaptain::checkDestFolder(const ustring& path) {
        if (path.empty()) {

        }
        return false;
    }

    /**
     * 
     * @return 
     */
    bool
    FileCaptain::isDirectory(const ustring& path) {
        return false;
    }

    /**
     * 
     * @return 
     */
    bool
    FileCaptain::isFile(const ustring& path) {
        return false;
    }


}
