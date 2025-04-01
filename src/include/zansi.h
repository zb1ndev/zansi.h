/* zansi.h - v0.0.1 - MIT License - https://github.com/zb1ndev/zansi.h 

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

    WARNING : Depends on https://github.com/zb1ndev/zstring.h 

*/

/* Goal for zansi.h :
    - Basically Raylib but for terminal
        - DrawRectangle(x,y,w,h,Color), etc.
        - This means I need to make a draw loop and basically append commands and then execute them all at once
          instead of just executing them immediately like we are doing now. 
*/

#if !defined(Z_ANSI_H)
#define Z_ANSI_H

    #include <stdio.h>

    #define Z_STRING_IMPLEMENTATION
    #include "zstring.h"

#pragma region Colors

    #define set_color(color)           "\e[0;"color
    #define set_bold(color)             "\e[1;"color
    #define set_underline(color)        "\e[4;"color
    
    #define fg(color) "3"color
    #define bg(color) "4"color

    /* Brighter version of ```fg```. */
    #define fgb(color) "7"color

    /* Brighter version of ```bg```. */
    #define bgb(color) "10"color

    #define BLACK           "0m"   
    #define RED             "1m"  
    #define GREEN           "2m"  
    #define YELLOW          "3m"  
    #define BLUE            "4m" 
    #define PURPLE          "5m"  
    #define CYAN            "6m"  
    #define WHITE           "7m"

    #define reset           "\e[0m"

#pragma endregion
#pragma region Cursor

    typedef enum CursorDir {
        Up      = 'A', 
        Down    = 'B', 
        Right   = 'C',
        Left    = 'D' 
    } CursorDir;

#pragma endregion

    /** A function that shifts cursor by ```amount``` in ```direction```.
     * @param direction The direction you want to shift the cursor.
     * @param amount The amount you want to shift the cursor.
     */
    void move_cursor_by(CursorDir direction, ssize_t amount);
    
    /** A function that shifts cursor in ```direction```.
     * @param direction The direction you want to shift the cursor.
     */
    void move_cursor(CursorDir direction); 

    /** A function that sets the cursor's position to home.
     */
    void set_cursor_home();

    /** A function that sets the cursor's position to ```x```, ```y```.
     * @param x The X position of the cursor.
     * @param y The Y position of the cursor.
     */
    void set_cursor_position(ssize_t x, ssize_t y);

#if defined(Z_ANSI_IMPLEMENTATION)

    void move_cursor_by(CursorDir direction, ssize_t amount) {
        printf("\033[%ld%c", amount, direction);
    }

    void move_cursor(CursorDir direction) {
        move_cursor_by(direction, 1);
    }

    void set_cursor_home() {
        printf("\033[H");
    }

    void set_cursor_position(ssize_t x, ssize_t y) {
        printf("\033[%ld;%ldH", x, y);
    }

#endif
#endif