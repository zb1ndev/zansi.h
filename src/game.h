#if !defined(GAME_H)
#define GAME_H

    #include <stdlib.h>

    #define Z_ANSI_IMPLEMENTATION
    #include "include/zansi.h"

    struct Player {
            
        int x, y;
        const char* color;

    };

    struct Game {
        
        char paused, quit;
        char board[20][20];

    };

    void get_input(struct Game* game, struct Player* player, int input) {

        switch (input) {

            case 'p':
                game->paused = 1;
                break;
            case 'w':
                player->y--;
                break;
            case Up:
                player->y--;
                break;

            case 'a':
                player->x--;
                break;
            case Left:
                player->x--;
                break;

            case 's':
                player->y++;
                break;
            case Down:
                player->y++;
                break;

            case 'd':
                player->x++;
                break;
            case Right:
                player->x++;
                break;

        default:
            break;
        }

    }

    void check_collision(struct Player* player, int input) {

    }

    void show_player_info(struct Player* player) {
        printf("\n\n%sPlayer Position%s :(%d,%d) | %sWASD%s or %sArrow Keys%s to move | Press '%sp%s' to pause", 
            player->color, z_reset_style(), player->x, player->y,
            z_set_color(z_fg(Z_BLUE)),
            z_reset_style(),
            z_set_color(z_fg(Z_BLUE)),
            z_reset_style(),
            z_set_color(z_fg(Z_BLUE)),
            z_reset_style()
        );
    }

    struct Game init_game() {

        struct Game result;
        result.paused = 0;
        result.quit = 0;

        for (size_t y = 0; y < 20; y++)
            for (size_t x = 0; x < 20; x++) 
                result.board[y][x] = '-';
        
        return result;

    }

    void render_game(struct Player* player, struct Game* game) {

        int position = 0;
        while (game->paused == 1) {

            z_clear_screen_and_set_home();
            const char* continue_style = ((position == 0) ? z_set_color(z_fg(Z_BLUE))"> Continue\n" : "  Continue\n");
            const char* quit_style = ((position == 1) ? z_set_color(z_fg(Z_BLUE))"> Quit\n" : "  Quit\n");
            printf("Paused :\n%s"z_reset_style()"%s"z_reset_style(), continue_style, quit_style);
            
            int input = z_get_char_raw();
            if (position == 0 && input == '\n') {
                z_clear_screen_and_set_home();
                game->paused = 0;
            }
            if (position == 1 && input == '\n') {
                z_clear_screen_and_set_home();
                game->quit = 1;
                return;
            }

            position = (input == Up) ? 0 : (input == Down) ? 1 : position;

        }

        // Render Game
        for (size_t y = 0, p = 0; y < 20; y++) {
            p = (y == player->y) ? 1 : 0;
            for (size_t x = 0; x < 20; x++) {
                if (x == player->x && p == 1)
                    printf(" %so "z_reset_style(), player->color);
                else printf(" %c ", game->board[y][x]);
            }
            printf("\n");
        }
        show_player_info(player);

    }

    void test_game() {

        z_clear_screen_and_set_home();

        int input = 0;
        struct Game game = init_game();
        struct Player player = (struct Player){0, 0, z_set_color(z_fg(Z_BLUE))};
        
        while (game.quit != 1) {

            render_game(&player, &game);

            if (game.quit != 1) {
            
                input = z_get_char_raw();
                get_input(&game, &player, input);
                check_collision(&player, input);
                z_clear_screen_and_set_home();

            }
            
        }

    }

#endif // GAME_H