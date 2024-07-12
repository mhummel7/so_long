/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:57:13 by mhummel           #+#    #+#             */
/*   Updated: 2024/07/02 09:41:05 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game_state *state)
{
	int	i;

	i = 0;
	while (i < state->map.height)
	{
		free(state->map.data[i]);
		i++;
	}
	free(state->map.data);
}

static int	process_line(t_game_state *state, char *line)
{
	size_t	line_length;

	line_length = ft_strlen(line);
	if (line_length > 0 && (line[line_length - 1] == '\n' || line[line_length
				- 1] == '\r'))
		line_length--;
	if (line_length > 0)
	{
		if (state->map.width == 0)
			state->map.width = line_length;
		else if (line_length != (size_t)state->map.width)
			return (0);
		state->map.height++;
	}
	return (1);
}

static void	init_map_dimensions(t_game_state *state, int fd)
{
	char	*line;

	state->map.height = 0;
	state->map.width = 0;
	line = get_next_line(fd);
	while (line && state->map.height < MAX_MAP_HEIGHT)
	{
		if (!process_line(state, line))
		{
			ft_printf("Error\nMap is not rectangular\n");
			close(fd);
			free(line);
			exit(1);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
}

void	load_map(t_game_state *state, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nCould not open file %s\n", filename);
		exit(1);
	}
	init_map_dimensions(state, fd);
	close(fd);
	allocate_map_memory(state);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nCould not reopen file %s\n", filename);
		free_map(state);
		exit(1);
	}
	read_map_data(state, fd);
	close(fd);
	validate_and_check_path(state);
}
