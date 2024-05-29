/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:40:29 by mhummel           #+#    #+#             */
/*   Updated: 2024/05/29 13:40:34 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
		return ;
	if (game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
	{
		printf("You won in %d moves!\n", game->moves);
		free_game(game);
	}
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	printf("Moves: %d\n", game->moves);
	render_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
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

int	close_game(t_game *game)
{
	free_game(game);
	return (0);
}