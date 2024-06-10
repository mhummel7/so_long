/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:42:20 by mhummel           #+#    #+#             */
/*   Updated: 2024/05/31 11:56:59 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_map(t_game *game, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening map file");
        exit(1);
    }

    char line[1024];
    int lines_allocated = 0;
    game->height = 0;

    while (fgets(line, sizeof(line), file)) {
        if (game->height == lines_allocated) {
            lines_allocated += 10;
            game->map = realloc(game->map, lines_allocated * sizeof(char *));
        }
        game->map[game->height] = strdup(line);
        game->map[game->height][strcspn(game->map[game->height], "\n")] = 0;
        game->height++;
    }

    game->width = strlen(game->map[0]);

    // Validate map
    int start_count = 0;
    int exit_count = 0;
    game->collectibles = 0;

    for (int y = 0; y < game->height; y++) {
        if ((int)strlen(game->map[y]) != game->width) {  // Casting size_t to int
            fprintf(stderr, "Error: Map is not rectangular\n");
            exit(1);
        }
        for (int x = 0; x < game->width; x++) {
            char tile = game->map[y][x];
            if (tile == 'P') start_count++;
            if (tile == 'E') exit_count++;
            if (tile == 'C') game->collectibles++;
            if (tile != '0' && tile != '1' && tile != 'C' && tile != 'E' && tile != 'P') {
                fprintf(stderr, "Error: Invalid character in map\n");
                exit(1);
            }
        }
    }

    if (start_count != 1 || exit_count != 1 || game->collectibles < 1) {
        fprintf(stderr, "Error: Map must have exactly one start (P), one exit (E), and at least one collectible (C)\n");
        exit(1);
    }

    fclose(file);
}
