/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:38:05 by mhummel           #+#    #+#             */
/*   Updated: 2024/05/31 14:57:27 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "./minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "keysym.h"
# include "X.h"

typedef struct
{
	void	*mlx;
	void	*win;
	void	*player_img;
	void	*wall_img;
	void	*collectible_img;
	void	*exit_img;
	void	*empty_img;
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
}			t_game;

void		init_game(t_game *game);
void		load_map(t_game *game, const char *filename);
void		render_map(t_game *game);
void		render(t_game *game);
void		move_player(t_game *game, int dx, int dy);
void		free_game(t_game *game);
int			handle_keypress(int keycode, t_game *game);
int			close_game(t_game *game);
int			render_map_handler(void *param);

#endif
