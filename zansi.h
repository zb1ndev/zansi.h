/* zansi.h - v1.0.0 - MIT License - https://github.com/zb1ndev/zansi.h 

    MIT License
    Copyright (c) 2025 Joel Zbinden

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

*/

#if !defined(Z_ANSI_H)
#define Z_ANSI_H

    #define Z_STRING_IMPLEMENTATION
    #include "zstring.h"

#pragma region Colors

    #define Normal(color)           "\e[0;"color
    #define Bold(color)             "\e[1;"color
    #define Underline(color)        "\e[4;"color
    #define Dim(color)              "\e[2;5;"color

    #define Forground(color) "3"color
    #define Background(color) "4"color

    #define Reset           "\e[0m"
    #define Black           "0m"   
    #define Red             "1m"  
    #define Green           "2m"  
    #define Yellow          "3m"  
    #define Blue            "4m" 
    #define Purple          "5m"  
    #define Cyan            "6m"  
    #define White           "7m"

#pragma endregion

    /** A function that creates a format specifier that shifts content by ```amount```.
     * @param amount The amount you want to shift the content.
     * @returns A string with a format specifier that shifts content by ```amount```.
     */
    char* align(ssize_t amount);

#if defined(Z_ANSI_IMPLEMENTATION)

    char* align(ssize_t amount) {
        return string_from_format("%%%ds", amount).content;
    }

#endif
#endif