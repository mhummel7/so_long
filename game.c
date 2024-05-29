/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:42:36 by mhummel           #+#    #+#             */
/*   Updated: 2024/05/29 13:42:43 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, 640, 480, "so_long");
	game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&game->width, &game->height);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&game->width, &game->height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &game->width, &game->height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&game->width, &game->height);
	game->empty_img = mlx_xpm_file_to_image(game->mlx, "textures/empty.xpm",
			&game->width, &game->height);
	game->collectibles = 0;
	game->moves = 0;
}

void	free_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->player_img);
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->collectible_img);
	mlx_destroy_image(game->mlx, game->exit_img);
	mlx_destroy_image(game->mlx, game->empty_img);
	for (int i = 0; i < game->height; i++)
	{
		free(game->map[i]);
	}
	free(game->map);
	exit(0);
}
