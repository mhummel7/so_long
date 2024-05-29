/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:42:20 by mhummel           #+#    #+#             */
/*   Updated: 2024/05/29 13:42:25 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_map(t_game *game, const char *filename)
{
	FILE	*file;

	file = fopen(filename, "r");
	if (!file)
	{
		perror("Error opening map file");
		exit(1);
	}
	// TODO: Read map dimensions, allocate memory and load map
	// This example assumes fixed map dimensions for simplicity
	game->width = 10;
	game->height = 10;
	game->map = malloc(game->height * sizeof(char *));
	for (int i = 0; i < game->height; i++)
	{
		game->map[i] = malloc(game->width + 1);
		if (fgets(game->map[i], game->width + 1, file) == NULL)
		{
			perror("Error reading map file");
			exit(1);
		}
		// Removing the newline character
		game->map[i][strcspn(game->map[i], "\n")] = 0;
	}
	fclose(file);
}
