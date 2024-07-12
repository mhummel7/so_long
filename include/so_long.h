/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:56:45 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/10 09:50:30 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/libft/libft/libft.h"

# define MAX_MAP_HEIGHT 100
# define MAX_MAP_WIDTH 100
# define TILE_SIZE 64

typedef struct s_map_element {
	char	symbol;
	char	*png_file;
}	t_map_element;

typedef struct s_game_assets {
	t_map_element	elements[5];
}	t_game_assets;

typedef struct s_player {
	int	x;
	int	y;
}	t_player;

typedef struct s_map {
	char	**data;
	int		width;
	int		height;
}	t_map;

typedef struct s_game_state {
	t_map			map;
	int				total_collectibles;
	int				collected_collectibles;
	t_player		player;
	mlx_t			*mlx;
	int				move_count;
	t_game_assets	assets;
	int				new_x;
	int				new_y;
	int				old_x;
	int				old_y;
}	t_game_state;

typedef struct s_dfs_state {
	bool	**visited;
	bool	found_exit;
	int		collectibles_found;
}	t_dfs_state;

// Function prototypes
void	free_map(t_game_state *state);
void	load_map(t_game_state *state, const char *filename);
void	validate_map_config(t_game_state *state);
void	validate_map_walls(t_game_state *state);
bool	check_valid_path(t_game_state *state);
void	draw_tile(t_game_state *state, char symbol, int x, int y);
void	display_map(t_game_state *state);
void	update_map_and_display(t_game_state *state, int old_x, int old_y);
void	key_hook(mlx_key_data_t keydata, void *param);
int		is_valid_ber_file(const char *filename);

// Utility functions
bool	check_valid_path(t_game_state *game);
bool	**create_visited_array(t_game_state *game);
void	free_visited_array(t_game_state *game, bool **visited);
void	allocate_map_memory(t_game_state *state);
void	process_map_line(t_game_state *state, char *line, int y);
void	read_map_data(t_game_state *state, int fd);
void	validate_and_check_path(t_game_state *state);

#endif
