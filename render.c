/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:40:47 by mhummel           #+#    #+#             */
/*   Updated: 2024/05/29 13:40:54 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(t_game *game)
{
			void *img;

	for (int y = 0; y < game->height; y++)
	{
		for (int x = 0; x < game->width; x++)
		{
			if (game->map[y][x] == '1')
				img = game->wall_img;
			else if (game->map[y][x] == 'C')
				img = game->collectible_img;
			else if (game->map[y][x] == 'E')
				img = game->exit_img;
			else if (game->map[y][x] == 'P')
			{
				img = game->player_img;
				game->player_x = x;
				game->player_y = y;
			}
			else
				img = game->empty_img;
			mlx_put_image_to_window(game->mlx, game->win, img, x * 64, y * 64);
		}
	}
}
