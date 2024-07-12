/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:57:47 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/01 14:49:18 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_texture_t	*load_texture(t_game_state *state, char symbol)
{
	int				i;
	mlx_texture_t	*texture;

	i = 0;
	while (i < 5)
	{
		if (state->assets.elements[i].symbol == symbol)
		{
			texture = mlx_load_png(state->assets.elements[i].png_file);
			if (!texture)
			{
				ft_printf("Error\nCould not load texture %s\n",
					state->assets.elements[i].png_file);
				exit(1);
			}
			return (texture);
		}
		i++;
	}
	return (NULL);
}

static void	create_image(t_game_state *state, mlx_texture_t *texture, int x,
		int y)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(state->mlx, texture);
	if (!img)
	{
		ft_printf("Error\nCould not convert texture to image\n");
		mlx_delete_texture(texture);
		exit(1);
	}
	mlx_image_to_window(state->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
	mlx_delete_texture(texture);
}

void	draw_tile(t_game_state *state, char symbol, int x, int y)
{
	mlx_texture_t	*texture;

	texture = load_texture(state, symbol);
	if (texture)
		create_image(state, texture, x, y);
}

void	display_map(t_game_state *state)
{
	int	x;
	int	y;

	y = 0;
	while (y < state->map.height)
	{
		x = 0;
		while (x < state->map.width)
		{
			draw_tile(state, state->map.data[y][x], x, y);
			x++;
		}
		y++;
	}
}
