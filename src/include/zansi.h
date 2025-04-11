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

    Version 0.1.1 Change-Log :
    - Added Colors
    - Added Cursor Movement
        - void z_move_cursor_by(Z_CursorDir direction, ssize_t amount);
        - void z_move_cursor(Z_CursorDir direction); 
        - void z_set_cursor_home();
        - void z_set_cursor_position(ssize_t x, ssize_t y);
    Added void z_clear_line();
    Added void z_clear_screen();
    Added void z_clear_screen_and_set_home();

    Version 1.0.0 Change-Log :
    - Made improvements to cursor movement

*/

#if !defined(Z_ANSI_H)
#define Z_ANSI_H

    #include <stdio.h>

    #define ssize_t signed long
    
    typedef enum Z_Direction {
        Up      = 'A', 
        Down    = 'B', 
        Right   = 'C',
        Left    = 'D' 
    } Z_Direction;

    #if defined(unix)

        #include <termios.h> // termios, TCSANOW, ECHO, ICANON
        #include <unistd.h>

        typedef struct Z_TerminalContext {

            struct termios old;
            struct termios new;

        } Z_TerminalContext;

    #elif defined(_WIN32)
    
        // Win32 Implementation

    #endif

    #pragma region Colors

        /** A macro that creates a character that sets the text color to ```color```.
         * @param color The color you want to set the text to.
         */
        #define z_set_color(color)           "\e[0;"color

        /** A macro that creates a character that sets the style to bold with ```color```.
         * @param color The color you want to set the text to.
         */
        #define z_set_bold(color)             "\e[1;"color

        /** A macro that creates a character that sets the style to underline with ```color```.
         * @param color The color you want to set the text to.
         */
        #define z_set_underline(color)        "\e[4;"color
        
        /** A macro that creates a character that sets the foreground text color to ```color```.
         * @param color The color you want to set the text to.
         */
        #define z_fg(color) "3"color

        /** A macro that creates a character that sets the background text color to ```color```.
         * @param color The color you want to set the background to.
         */
        #define z_bg(color) "4"color

        /* Brighter version of ```fg```. */
        #define z_fgb(color) "7"color

        /* Brighter version of ```bg```. */
        #define z_bgb(color) "10"color

        #define Z_BLACK           "0m"   
        #define Z_RED             "1m"  
        #define Z_GREEN           "2m"  
        #define Z_YELLOW          "3m"  
        #define Z_BLUE            "4m" 
        #define Z_PURPLE          "5m"  
        #define Z_CYAN            "6m"  
        #define Z_WHITE           "7m"

        /* Resets text color and style to default. */
        #define z_reset_style()         "\e[0m"

    #pragma endregion

    /** A function enables ```raw mode```. ( Allows for getting input without the need for the user to press enter )
     * @param context The terminal context.
     */
    void z_enable_raw(Z_TerminalContext* context);

    /** A function disables ```raw mode```. ( Allows for getting input without the need for the user to press enter )
     * @param context The terminal context.
     */
    void z_disable_raw(Z_TerminalContext* context);

    /** A function that gets a character without the need for the user to press enter.
     * @returns The character the user pressed.
     */
    int z_get_char_raw();

    /** A function that shifts cursor by ```amount``` in ```direction```.
     * @param direction The direction you want to shift the cursor.
     * @param amount The amount you want to shift the cursor.
     * @param offset Typically for the length of string printed before hand.
     */
    void z_move_cursor_by(Z_Direction direction, ssize_t amount, ssize_t offset);
    
    /** A function that shifts cursor in ```direction```.
     * @param direction The direction you want to shift the cursor.
     * @param offset Typically for the length of string printed before hand.
     */
    void z_move_cursor(Z_Direction direction, ssize_t offset); 

    /** A function that sets the cursor's position to home.
     */
    void z_set_cursor_home();

    /** A function that sets the cursor's position to ```x```, ```y```.
     * @param x The X position of the cursor.
     * @param y The Y position of the cursor.
     */
    void z_set_cursor_position(ssize_t x, ssize_t y);

    /** A function that clears the line where the cursor is positioned.
     */
    void z_clear_line();

    /** A function that clears the screen.
     */
    void z_clear_screen();

    /** A function that clears the screen and sets the cursor's position to home.
     */
    void z_clear_screen_and_set_home();

#if defined(Z_ANSI_IMPLEMENTATION)

    #if defined(unix)

        void z_enable_raw(Z_TerminalContext* context) {

            tcgetattr(STDIN_FILENO, &context->old);
            context->new = context->old;
            context->new.c_lflag &= ~(ICANON);          
            tcsetattr(STDIN_FILENO, TCSANOW, &context->new);
            
        }

        
        void z_disable_raw(Z_TerminalContext* context) {

            tcsetattr(STDIN_FILENO, TCSANOW, &context->old);

        }

        int z_get_char_raw() {

            Z_TerminalContext context;
            z_enable_raw(&context);
            int result = getchar();
            
            // For Arrow Keys
            if (result == 27)
                if (getchar() == 91) 
                    result = getchar();
            z_disable_raw(&context);

            return result;

        }

    #elif defined(_WIN32)

        // Win32 Implementation

    #endif

    void z_move_cursor_by(Z_Direction direction, ssize_t amount, ssize_t offset) {
        printf("\033[%ld%c", amount + offset, direction);
    }

    void z_move_cursor(Z_Direction direction, ssize_t offset) {

        switch (direction) {
        case Up:
            z_move_cursor_by(Left, 3, offset);
            z_move_cursor_by(Up, 1, 0);
            break;
        case Down:
            z_move_cursor_by(Left, 3, offset);
            z_move_cursor_by(Down, 1, 0);
            break;
        case Right:
            z_move_cursor_by(Left, 3, offset);
            z_move_cursor_by(Right, 1, 0);
            break;
        case Left:
            z_move_cursor_by(Left, 4, offset);
        default:
            break;
        }        

    }

    void z_set_cursor_home() {
        printf("\033[H");
    }

    void z_set_cursor_position(ssize_t x, ssize_t y) {
        printf("\033[%ld;%ldH", x, y);
    }

    void z_clear_line() {
        printf("\033[2K");
    }

    void z_clear_screen() {
        printf("\033[2J");
    }

    void z_clear_screen_and_set_home() {
        z_clear_screen();
        z_set_cursor_home();
    }

#endif
#endif