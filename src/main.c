/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 08:26:33 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/10 09:55:13 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error\nUsage: %s <map_file.ber>\n", argv[0]);
		return (0);
	}
	if (!is_valid_ber_file(argv[1]))
	{
		ft_printf("Error\nInvalid map file extension. Must be .ber\n");
		return (0);
	}
	return (1);
}

static int	initialize_game(t_game_state *state, char *map_file)
{
	mlx_t	*mlx;

	load_map(state, map_file);
	mlx = mlx_init(state->map.width * TILE_SIZE, state->map.height * TILE_SIZE,
			"so_long", true);
	if (!mlx)
	{
		ft_printf("Error\nCould not initialize MLX\n");
		free_map(state);
		return (0);
	}
	state->mlx = mlx;
	state->move_count = 0;
	return (1);
}

static void	initialize_assets(t_game_state *state)
{
	state->assets.elements[0] = (t_map_element){'1', "src/textures/wall.png"};
	state->assets.elements[1] = (t_map_element){'0', "src/textures/floor.png"};
	state->assets.elements[2] = (t_map_element){'E', "src/textures/exit.png"};
	state->assets.elements[3] = (t_map_element){'P', "src/textures/player.png"};
	state->assets.elements[4] = (t_map_element){'C',
		"src/textures/collectible.png"};
}

int	main(int argc, char *argv[])
{
	t_game_state	state;

	ft_memset(&state, 0, sizeof(t_game_state));
	if (!check_arguments(argc, argv))
		return (1);
	initialize_assets(&state);
	if (!initialize_game(&state, argv[1]))
		return (1);
	display_map(&state);
	draw_tile(&state, 'P', state.player.x, state.player.y);
	ft_printf("\nGame has started\n\n");
	mlx_key_hook(state.mlx, key_hook, &state);
	mlx_loop(state.mlx);
	mlx_terminate(state.mlx);
	free_map(&state);
	return (0);
}
