/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:57:30 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/26 11:21:22 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	count_map_elements(t_game_state *state, int *player_count,
		int *exit_count)
{
	int	x;
	int	y;

	y = -1;
	while (++y < state->map.height)
	{
		x = -1;
		while (++x < state->map.width)
		{
			if (state->map.data[y][x] == 'P')
			{
				(*player_count)++;
				state->player.x = x;
				state->player.y = y;
			}
			else if (state->map.data[y][x] == 'E')
				(*exit_count)++;
			else if (state->map.data[y][x] == 'C')
				state->total_collectibles++;
			else if (state->map.data[y][x] != '0'
				&& state->map.data[y][x] != '1')
				(ft_printf("Error\nInvalid character in map\n"), exit(1));
		}
	}
}

void	validate_map_config(t_game_state *state)
{
	int	player_count;
	int	exit_count;

	player_count = 0;
	exit_count = 0;
	state->total_collectibles = 0;
	count_map_elements(state, &player_count, &exit_count);
	if (player_count != 1 || exit_count != 1 || state->total_collectibles < 1)
	{
		ft_printf("Error\nInvalid map configuration\n");
		exit(1);
	}
}

static void	check_horizontal_walls(t_game_state *state)
{
	int	x;

	x = 0;
	while (x < state->map.width)
	{
		if (state->map.data[0][x] != '1' || state->map.data[state->map.height
			- 1][x] != '1')
		{
			ft_printf("Error\nMap is not enclosed by walls\n");
			exit(1);
		}
		x++;
	}
}

void	validate_map_walls(t_game_state *state)
{
	int	y;

	y = 0;
	while (y < state->map.height)
	{
		if (state->map.data[y][0] != '1' || state->map.data[y][state->map.width
			- 1] != '1')
		{
			ft_printf("Error\nMap is not enclosed by walls\n");
			exit(1);
		}
		y++;
	}
	check_horizontal_walls(state);
}

int	is_valid_ber_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}
