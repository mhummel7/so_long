/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:39:25 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/02 09:40:54 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_map_memory(t_game_state *state)
{
	int	i;

	state->map.data = malloc(state->map.height * sizeof(char *));
	i = 0;
	while (i < state->map.height)
	{
		state->map.data[i] = malloc((state->map.width + 1) * sizeof(char));
		i++;
	}
}

void	process_map_line(t_game_state *state, char *line, int y)
{
	size_t	line_length;

	line_length = ft_strlen(line);
	if (line_length > 0 && (line[line_length - 1] == '\n' || line[line_length
				- 1] == '\r'))
		line[--line_length] = '\0';
	if (line_length > 0)
	{
		ft_strncpy(state->map.data[y], line, state->map.width);
		state->map.data[y][state->map.width] = '\0';
	}
}

void	read_map_data(t_game_state *state, int fd)
{
	char	*line;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line && y < state->map.height)
	{
		process_map_line(state, line, y);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

void	validate_and_check_path(t_game_state *state)
{
	validate_map_config(state);
	validate_map_walls(state);
	if (!check_valid_path(state))
	{
		free_map(state);
		exit(1);
	}
}
