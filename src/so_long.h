/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:56:45 by mhummel           #+#    #+#             */
/*   Updated: 2024/06/11 12:55:33 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

typedef struct s_map
{
	char		**map; // Map array
	int			width; // Map width
	int			height; // Map height
	int			collectibles; // Number of collectibles
	int			player_x; // Player x position
	int			player_y; // Player y position
	int			moves; // Number of moves
	void		*mlx;
	void		*win;
	void		*wall_img;
	void		*player_img;
	void		*collectible_img;
	void		*exit_img;
	void		*floor_img;
}	t_game;

#endif