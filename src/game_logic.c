/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:58:01 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/02 14:24:11 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_collectible(t_game_state *state)
{
	if (state->map.data[state->player.y][state->player.x] == 'C')
	{
		state->collected_collectibles++;
		state->map.data[state->player.y][state->player.x] = '0';
	}
}

static void	handle_exit(t_game_state *state)
{
	if (state->map.data[state->player.y][state->player.x] == 'E')
	{
		if (state->collected_collectibles == state->total_collectibles)
		{
			ft_printf("\033[0;32m");
			ft_printf("Congratulations! You've completed the game "
				"in %d moves.\n\n", state->move_count);
			ft_printf("\033[0;0m");
			mlx_close_window(state->mlx);
		}
		else
		{
			ft_printf("\033[0;34m");
			ft_printf("You need to collect all items before exiting!\n");
			ft_printf("\033[0;0m");
		}
	}
}

void	update_map_and_display(t_game_state *state, int old_x, int old_y)
{
	if (state->map.data[old_y][old_x] != 'E')
	{
		state->map.data[old_y][old_x] = '0';
		draw_tile(state, '0', old_x, old_y);
	}
	else
		draw_tile(state, 'E', old_x, old_y);
	handle_collectible(state);
	handle_exit(state);
	draw_tile(state, 'P', state->player.x, state->player.y);
}

static void	move_player(t_game_state *state)
{
	int	old_x;
	int	old_y;

	if (state->new_x >= 0 && state->new_x < state->map.width
		&& state->new_y >= 0 && state->new_y < state->map.height
		&& state->map.data[state->new_y][state->new_x] != '1')
	{
		old_x = state->player.x;
		old_y = state->player.y;
		state->player.x = state->new_x;
		state->player.y = state->new_y;
		state->move_count++;
		ft_printf("\033[0;33m");
		ft_printf("Moves: %d\n", state->move_count);
		ft_printf("\033[0;0m");
		update_map_and_display(state, old_x, old_y);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game_state	*state;

	state = (t_game_state *)param;
	state->new_x = state->player.x;
	state->new_y = state->player.y;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
			state->new_y -= 1;
		else if (keydata.key == MLX_KEY_A)
			state->new_x -= 1;
		else if (keydata.key == MLX_KEY_S)
			state->new_y += 1;
		else if (keydata.key == MLX_KEY_D)
			state->new_x += 1;
		else if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(state->mlx);
			return ;
		}
		else
			return ;
		move_player(state);
	}
}
