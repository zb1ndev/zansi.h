#define Z_ANSI_IMPLEMENTATION
#include "include/zansi.h"
#include "game.h"

#pragma region TESTS

    void test_move_string() {

        z_clear_screen_and_set_home();

        int input = 0;
        while (input != 'q') {

            printf("( Press 'q' to quit )");     // Length of 22
            input = z_get_char_raw();
            z_move_cursor(input, 22 + 3);            // Offset of 22
            z_clear_screen();

        }

        z_clear_screen_and_set_home();

    }

    void test_menu() {

        int position = 0;    
        while (1) {

            z_clear_screen_and_set_home();

            const char* movement_demo_style = ((position == 0) ? z_set_color(z_fg(Z_BLUE))"> Movement Demo\n" : "  Movement Demo\n");
            const char* game_style = ((position == 1) ? z_set_color(z_fg(Z_BLUE))"> Play Game\n" : "  Play Game\n");
            const char* quit_style = ((position == 2) ? z_set_color(z_fg(Z_BLUE))"> Quit\n" : "  Quit\n");
            
            printf("%s"z_reset_style()"%s"z_reset_style()"%s"z_reset_style(), movement_demo_style, game_style, quit_style);
            
            int dir = z_get_char_raw();
            if (dir == '\n' && position == 0)
                test_move_string();
            else if (dir == '\n' && position == 1)
                test_game();
            else if (dir == '\n' && position == 2)
                break;
            position = ((dir == Up) ? position-1 : (dir == Down) ? position+1 : position) % 3;

        }

    }

#pragma endregion

int main() {

    test_menu();
    return 0;

}