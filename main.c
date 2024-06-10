/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:42:53 by mhummel           #+#    #+#             */
/*   Updated: 2024/05/31 14:37:01 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv) {
    t_game game;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    memset(&game, 0, sizeof(t_game));
    game.mlx = mlx_init();
    if (!game.mlx) {
        perror("mlx_init");
        exit(EXIT_FAILURE);
    }

    game.map = NULL; // Initialisiere game->map mit NULL

    load_map(&game, argv[1]);

    // Hier wird die KeyPress-Callback-Funktion registriert
    mlx_hook(game.win, KeyPress, KeyPressMask, &handle_keypress, &game);
    mlx_loop_hook(game.mlx, &render_map_handler, &game); // Korrekte Signatur der Funktion render_map_handler
    mlx_loop(game.mlx);

    return 0;
}

int render_map_handler(void *param) {
    t_game *game = (t_game *)param;
    render_map(game); // Aufruf von render_map mit dem t_game-Zeiger
    return 0;
}

int handle_keypress(int keycode, t_game *game) {
	printf("Key pressed main.c: %d\n", keycode);
    if (keycode == 53) // Escape key
        free_game(game);
    if (keycode == 13) // W key
        move_player(game, 0, -1);
    if (keycode == 1) // S key
        move_player(game, 0, 1);
    if (keycode == 0) // A key
        move_player(game, -1, 0);
    if (keycode == 2) // D key
        move_player(game, 1, 0);
    return (0);
}

int close_game(t_game *game) {
    free_game(game);
    return (0);
}
