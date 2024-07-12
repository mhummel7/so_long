/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:33:59 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/01 14:25:22 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	is_valid_move(t_game_state *game, int x, int y, t_dfs_state *state)
{
	return (x >= 0 && x < game->map.width && y >= 0 && y < game->map.height
		&& !state->visited[y][x] && game->map.data[y][x] != '1');
}

static void	update_state(t_game_state *game, int x, int y, t_dfs_state *state)
{
	state->visited[y][x] = true;
	if (game->map.data[y][x] == 'C')
		state->collectibles_found++;
	else if (game->map.data[y][x] == 'E')
		state->found_exit = true;
}

static bool	dfs(t_game_state *game, int x, int y, t_dfs_state *state)
{
	int	dx[4];
	int	dy[4];
	int	i;

	dx[0] = 0;
	dx[1] = 0;
	dx[2] = 1;
	dx[3] = -1;
	dy[0] = 1;
	dy[1] = -1;
	dy[2] = 0;
	dy[3] = 0;
	if (!is_valid_move(game, x, y, state))
		return (false);
	update_state(game, x, y, state);
	i = 0;
	while (i < 4)
	{
		dfs(game, x + dx[i], y + dy[i], state);
		i++;
	}
	return (state->found_exit
		&& state->collectibles_found == game->total_collectibles);
}

bool	check_valid_path(t_game_state *game)
{
	t_dfs_state	state;
	bool		result;

	state.visited = create_visited_array(game);
	if (!state.visited)
	{
		ft_printf("Error\nMemory allocation failed\n");
		return (false);
	}
	state.found_exit = false;
	state.collectibles_found = 0;
	result = dfs(game, game->player.x, game->player.y, &state);
	free_visited_array(game, state.visited);
	if (!result)
	{
		ft_printf("Error\nNo valid path to exit or all collectibles\n");
		return (false);
	}
	return (true);
}
